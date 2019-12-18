void
load_if_names()
{
# if NETINET6 && defined(SIOCGLIFCONF)
#  ifdef __hpux

    /*
    **  Unfortunately, HP has changed all of the structures,
    **  making life difficult for implementors.
    */

#   define lifconf	if_laddrconf
#   define lifc_len	iflc_len
#   define lifc_buf	iflc_buf
#   define lifreq	if_laddrreq
#   define lifr_addr	iflr_addr
#   define lifr_name	iflr_name
#   define lifr_flags	iflr_flags
#   define ss_family	sa_family
#   undef SIOCGLIFNUM
#  endif /* __hpux */

	int s;
	int i;
	size_t len;
	int numifs;
	char *buf;
	struct lifconf lifc;
#  ifdef SIOCGLIFNUM
	struct lifnum lifn;
#  endif /* SIOCGLIFNUM */

	s = socket(InetMode, SOCK_DGRAM, 0);
	if (s == -1)
		return;

	/* get the list of known IP address from the kernel */
#  ifdef __hpux
	i = ioctl(s, SIOCGIFNUM, (char *) &numifs);
#  endif /* __hpux */
#  ifdef SIOCGLIFNUM
	lifn.lifn_family = AF_UNSPEC;
	lifn.lifn_flags = 0;
	i = ioctl(s, SIOCGLIFNUM, (char *)&lifn);
	numifs = lifn.lifn_count;
#  endif /* SIOCGLIFNUM */

#  if defined(__hpux) || defined(SIOCGLIFNUM)
	if (i < 0)
	{
		/* can't get number of interfaces -- fall back */
		if (tTd(0, 4))
			sm_dprintf("SIOCGLIFNUM failed: %s\n",
				   sm_errstring(errno));
		numifs = -1;
	}
	else if (tTd(0, 42))
		sm_dprintf("system has %d interfaces\n", numifs);
	if (numifs < 0)
#  endif /* defined(__hpux) || defined(SIOCGLIFNUM) */
		numifs = MAXINTERFACES;

	if (numifs <= 0)
	{
		(void) close(s);
		return;
	}

	len = lifc.lifc_len = numifs * sizeof(struct lifreq);
	buf = lifc.lifc_buf = xalloc(lifc.lifc_len);
#  ifndef __hpux
	lifc.lifc_family = AF_UNSPEC;
	lifc.lifc_flags = 0;
#  endif /* ! __hpux */
	if (ioctl(s, SIOCGLIFCONF, (char *)&lifc) < 0)
	{
		if (tTd(0, 4))
			sm_dprintf("SIOCGLIFCONF failed: %s\n",
				   sm_errstring(errno));
		(void) close(s);
		sm_free(buf);
		return;
	}

	/* scan the list of IP address */
	if (tTd(0, 40))
		sm_dprintf("scanning for interface specific names, lifc_len=%ld\n",
			   (long) len);

	for (i = 0; i < len && i >= 0; )
	{
		int flags;
		struct lifreq *ifr = (struct lifreq *)&buf[i];
		SOCKADDR *sa = (SOCKADDR *) &ifr->lifr_addr;
		int af = ifr->lifr_addr.ss_family;
		char *addr;
		char *name;
		struct in6_addr ia6;
		struct in_addr ia;
#  ifdef SIOCGLIFFLAGS
		struct lifreq ifrf;
#  endif /* SIOCGLIFFLAGS */
		char ip_addr[256];
		char buf6[INET6_ADDRSTRLEN];

		/*
		**  We must close and recreate the socket each time
		**  since we don't know what type of socket it is now
		**  (each status function may change it).
		*/

		(void) close(s);

		s = socket(af, SOCK_DGRAM, 0);
		if (s == -1)
		{
			sm_free(buf); /* XXX */
			return;
		}

		/*
		**  If we don't have a complete ifr structure,
		**  don't try to use it.
		*/

		if ((len - i) < sizeof(*ifr))
			break;

#  ifdef BSD4_4_SOCKADDR
		if (sa->sa.sa_len > sizeof(ifr->lifr_addr))
			i += sizeof(ifr->lifr_name) + sa->sa.sa_len;
		else
#  endif /* BSD4_4_SOCKADDR */
#  ifdef DEC
			/* fix for IPv6  size differences */
			i += sizeof(ifr->ifr_name) +
			     max(sizeof(ifr->ifr_addr), ifr->ifr_addr.sa_len);
#   else /* DEC */
			i += sizeof(*ifr);
#   endif /* DEC */

		if (tTd(0, 20))
			sm_dprintf("%s\n", anynet_ntoa(sa));

		if (af != AF_INET && af != AF_INET6)
			continue;

#  ifdef SIOCGLIFFLAGS
		memset(&ifrf, '\0', sizeof(struct lifreq));
		(void) sm_strlcpy(ifrf.lifr_name, ifr->lifr_name,
				  sizeof(ifrf.lifr_name));
		if (ioctl(s, SIOCGLIFFLAGS, (char *) &ifrf) < 0)
		{
			if (tTd(0, 4))
				sm_dprintf("SIOCGLIFFLAGS failed: %s\n",
					   sm_errstring(errno));
			continue;
		}

		name = ifr->lifr_name;
		flags = ifrf.lifr_flags;

		if (tTd(0, 41))
			sm_dprintf("\tflags: %lx\n", (unsigned long) flags);

		if (!bitset(IFF_UP, flags))
			continue;
#  endif /* SIOCGLIFFLAGS */

		ip_addr[0] = '\0';

		/* extract IP address from the list*/
		switch (af)
		{
		  case AF_INET6:
			SETV6LOOPBACKADDRFOUND(*sa);
#  ifdef __KAME__
			/* convert into proper scoped address */
			if ((IN6_IS_ADDR_LINKLOCAL(&sa->sin6.sin6_addr) ||
			     IN6_IS_ADDR_SITELOCAL(&sa->sin6.sin6_addr)) &&
			    sa->sin6.sin6_scope_id == 0)
			{
				struct in6_addr *ia6p;

				ia6p = &sa->sin6.sin6_addr;
				sa->sin6.sin6_scope_id = ntohs(ia6p->s6_addr[3] |
							       ((unsigned int)ia6p->s6_addr[2] << 8));
				ia6p->s6_addr[2] = ia6p->s6_addr[3] = 0;
			}
#  endif /* __KAME__ */
			ia6 = sa->sin6.sin6_addr;
			if (IN6_IS_ADDR_UNSPECIFIED(&ia6))
			{
				addr = anynet_ntop(&ia6, buf6, sizeof(buf6));
				message("WARNING: interface %s is UP with %s address",
					name, addr == NULL ? "(NULL)" : addr);
				continue;
			}

			/* save IP address in text from */
			addr = anynet_ntop(&ia6, buf6, sizeof(buf6));
			if (addr != NULL)
				(void) sm_snprintf(ip_addr, sizeof(ip_addr),
						   "[%.*s]",
						   (int) sizeof(ip_addr) - 3,
						   addr);
			break;

		  case AF_INET:
			ia = sa->sin.sin_addr;
			if (ia.s_addr == INADDR_ANY ||
			    ia.s_addr == INADDR_NONE)
			{
				message("WARNING: interface %s is UP with %s address",
					name, inet_ntoa(ia));
				continue;
			}

			/* save IP address in text from */
			(void) sm_snprintf(ip_addr, sizeof(ip_addr), "[%.*s]",
					(int) sizeof(ip_addr) - 3, inet_ntoa(ia));
			break;
		}

		if (*ip_addr == '\0')
			continue;

		if (!wordinclass(ip_addr, 'w'))
		{
			setclass('w', ip_addr);
			if (tTd(0, 4))
				sm_dprintf("\ta.k.a.: %s\n", ip_addr);
		}

#  ifdef SIOCGLIFFLAGS
		/* skip "loopback" interface "lo" */
		if (DontProbeInterfaces == DPI_SKIPLOOPBACK &&
		    bitset(IFF_LOOPBACK, flags))
			continue;
#  endif /* SIOCGLIFFLAGS */
		(void) add_hostnames(sa);
	}
	sm_free(buf); /* XXX */
	(void) close(s);
# else /* NETINET6 && defined(SIOCGLIFCONF) */
#  if defined(SIOCGIFCONF) && !SIOCGIFCONF_IS_BROKEN
	int s;
	int i;
	struct ifconf ifc;
	int numifs;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == -1)
		return;

	/* get the list of known IP address from the kernel */
#   if defined(SIOCGIFNUM) && !SIOCGIFNUM_IS_BROKEN
	if (ioctl(s, SIOCGIFNUM, (char *) &numifs) < 0)
	{
		/* can't get number of interfaces -- fall back */
		if (tTd(0, 4))
			sm_dprintf("SIOCGIFNUM failed: %s\n",
				   sm_errstring(errno));
		numifs = -1;
	}
	else if (tTd(0, 42))
		sm_dprintf("system has %d interfaces\n", numifs);
	if (numifs < 0)
#   endif /* defined(SIOCGIFNUM) && !SIOCGIFNUM_IS_BROKEN */
		numifs = MAXINTERFACES;

	if (numifs <= 0)
	{
		(void) close(s);
		return;
	}
	ifc.ifc_len = numifs * sizeof(struct ifreq);
	ifc.ifc_buf = xalloc(ifc.ifc_len);
	if (ioctl(s, SIOCGIFCONF, (char *)&ifc) < 0)
	{
		if (tTd(0, 4))
			sm_dprintf("SIOCGIFCONF failed: %s\n",
				   sm_errstring(errno));
		(void) close(s);
		return;
	}

	/* scan the list of IP address */
	if (tTd(0, 40))
		sm_dprintf("scanning for interface specific names, ifc_len=%d\n",
			ifc.ifc_len);

	for (i = 0; i < ifc.ifc_len && i >= 0; )
	{
		int af;
		struct ifreq *ifr = (struct ifreq *) &ifc.ifc_buf[i];
		SOCKADDR *sa = (SOCKADDR *) &ifr->ifr_addr;
#   if NETINET6
		char *addr;
		struct in6_addr ia6;
#   endif /* NETINET6 */
		struct in_addr ia;
#   ifdef SIOCGIFFLAGS
		struct ifreq ifrf;
#   endif /* SIOCGIFFLAGS */
		char ip_addr[256];
#   if NETINET6
		char buf6[INET6_ADDRSTRLEN];
#   endif /* NETINET6 */

		/*
		**  If we don't have a complete ifr structure,
		**  don't try to use it.
		*/

		if ((ifc.ifc_len - i) < sizeof(*ifr))
			break;

#   ifdef BSD4_4_SOCKADDR
		if (sa->sa.sa_len > sizeof(ifr->ifr_addr))
			i += sizeof(ifr->ifr_name) + sa->sa.sa_len;
		else
#   endif /* BSD4_4_SOCKADDR */
			i += sizeof(*ifr);

		if (tTd(0, 20))
			sm_dprintf("%s\n", anynet_ntoa(sa));

		af = ifr->ifr_addr.sa_family;
		if (af != AF_INET
#   if NETINET6
		    && af != AF_INET6
#   endif /* NETINET6 */
		    )
			continue;

#   ifdef SIOCGIFFLAGS
		memset(&ifrf, '\0', sizeof(struct ifreq));
		(void) sm_strlcpy(ifrf.ifr_name, ifr->ifr_name,
			       sizeof(ifrf.ifr_name));
		(void) ioctl(s, SIOCGIFFLAGS, (char *) &ifrf);
		if (tTd(0, 41))
			sm_dprintf("\tflags: %lx\n",
				(unsigned long) ifrf.ifr_flags);
#    define IFRFREF ifrf
#   else /* SIOCGIFFLAGS */
#    define IFRFREF (*ifr)
#   endif /* SIOCGIFFLAGS */

		if (!bitset(IFF_UP, IFRFREF.ifr_flags))
			continue;

		ip_addr[0] = '\0';

		/* extract IP address from the list*/
		switch (af)
		{
		  case AF_INET:
			ia = sa->sin.sin_addr;
			if (ia.s_addr == INADDR_ANY ||
			    ia.s_addr == INADDR_NONE)
			{
				message("WARNING: interface %s is UP with %s address",
					ifr->ifr_name, inet_ntoa(ia));
				continue;
			}

			/* save IP address in text from */
			(void) sm_snprintf(ip_addr, sizeof(ip_addr), "[%.*s]",
					(int) sizeof(ip_addr) - 3,
					inet_ntoa(ia));
			break;

#   if NETINET6
		  case AF_INET6:
			SETV6LOOPBACKADDRFOUND(*sa);
#    ifdef __KAME__
			/* convert into proper scoped address */
			if ((IN6_IS_ADDR_LINKLOCAL(&sa->sin6.sin6_addr) ||
			     IN6_IS_ADDR_SITELOCAL(&sa->sin6.sin6_addr)) &&
			    sa->sin6.sin6_scope_id == 0)
			{
				struct in6_addr *ia6p;

				ia6p = &sa->sin6.sin6_addr;
				sa->sin6.sin6_scope_id = ntohs(ia6p->s6_addr[3] |
							       ((unsigned int)ia6p->s6_addr[2] << 8));
				ia6p->s6_addr[2] = ia6p->s6_addr[3] = 0;
			}
#    endif /* __KAME__ */
			ia6 = sa->sin6.sin6_addr;
			if (IN6_IS_ADDR_UNSPECIFIED(&ia6))
			{
				addr = anynet_ntop(&ia6, buf6, sizeof(buf6));
				message("WARNING: interface %s is UP with %s address",
					ifr->ifr_name,
					addr == NULL ? "(NULL)" : addr);
				continue;
			}

			/* save IP address in text from */
			addr = anynet_ntop(&ia6, buf6, sizeof(buf6));
			if (addr != NULL)
				(void) sm_snprintf(ip_addr, sizeof(ip_addr),
						   "[%.*s]",
						   (int) sizeof(ip_addr) - 3,
						   addr);
			break;

#   endif /* NETINET6 */
		}

		if (ip_addr[0] == '\0')
			continue;

		if (!wordinclass(ip_addr, 'w'))
		{
			setclass('w', ip_addr);
			if (tTd(0, 4))
				sm_dprintf("\ta.k.a.: %s\n", ip_addr);
		}

		/* skip "loopback" interface "lo" */
		if (DontProbeInterfaces == DPI_SKIPLOOPBACK &&
		    bitset(IFF_LOOPBACK, IFRFREF.ifr_flags))
			continue;

		(void) add_hostnames(sa);
	}
	sm_free(ifc.ifc_buf); /* XXX */
	(void) close(s);
#   undef IFRFREF
#  endif /* defined(SIOCGIFCONF) && !SIOCGIFCONF_IS_BROKEN */
# endif /* NETINET6 && defined(SIOCGLIFCONF) */
}