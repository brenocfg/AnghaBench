#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sockaddr_dl {size_t sdl_nlen; int /*<<< orphan*/  sdl_data; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct iface_addr {int /*<<< orphan*/  peer; int /*<<< orphan*/  ifa; } ;
struct iface {int addrs; struct iface_addr* addr; scalar_t__ mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/  index; int /*<<< orphan*/ * descr; int /*<<< orphan*/  name; } ;
struct ifa_msghdr {scalar_t__ ifam_type; int ifam_addrs; int /*<<< orphan*/  ifam_msglen; } ;
struct if_msghdr {scalar_t__ ifm_type; int /*<<< orphan*/  ifm_msglen; int /*<<< orphan*/  ifm_flags; int /*<<< orphan*/  ifm_index; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int CTL_NET ; 
 int ENOMEM ; 
 int NET_RT_IFLIST ; 
 int PF_ROUTE ; 
 size_t RTAX_BRD ; 
 size_t RTAX_IFA ; 
 int RTAX_MAX ; 
 size_t RTAX_NETMASK ; 
 int RTA_IFA ; 
 scalar_t__ RTM_IFINFO ; 
 scalar_t__ RTM_NEWADDR ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  iface_ParseHdr (struct ifa_msghdr*,struct sockaddr**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  ncpaddr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncpaddr_setsa (int /*<<< orphan*/ *,struct sockaddr*) ; 
 int /*<<< orphan*/  ncprange_setsa (int /*<<< orphan*/ *,struct sockaddr*,struct sockaddr*) ; 
 scalar_t__ realloc (struct iface_addr*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 char* strerror (int) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct iface *
iface_Create(const char *name)
{
  int mib[6], maxtries, err;
  size_t needed, namelen;
  char *buf, *ptr, *end;
  struct if_msghdr *ifm;
  struct ifa_msghdr *ifam;
  struct sockaddr_dl *dl;
  struct sockaddr *sa[RTAX_MAX];
  struct iface *iface;
  struct iface_addr *addr;

  mib[0] = CTL_NET;
  mib[1] = PF_ROUTE;
  mib[2] = 0;
  mib[3] = 0;
  mib[4] = NET_RT_IFLIST;
  mib[5] = 0;

  maxtries = 20;
  err = 0;
  do {
    if (maxtries-- == 0 || (err && err != ENOMEM)) {
      fprintf(stderr, "iface_Create: sysctl: %s\n", strerror(err));
      return NULL;
    }

    if (sysctl(mib, 6, NULL, &needed, NULL, 0) < 0) {
      fprintf(stderr, "iface_Create: sysctl: estimate: %s\n",
                strerror(errno));
      return NULL;
    }

    if ((buf = (char *)malloc(needed)) == NULL) {
      fprintf(stderr, "iface_Create: malloc failed: %s\n", strerror(errno));
      return NULL;
    }

    if (sysctl(mib, 6, buf, &needed, NULL, 0) < 0) {
      err = errno;
      free(buf);
      buf = NULL;
    }
  } while (buf == NULL);

  ptr = buf;
  end = buf + needed;
  iface = NULL;
  namelen = strlen(name);

  while (ptr < end && iface == NULL) {
    ifm = (struct if_msghdr *)ptr;			/* On if_msghdr */
    if (ifm->ifm_type != RTM_IFINFO)
      break;
    dl = (struct sockaddr_dl *)(ifm + 1);		/* Single _dl at end */
    if (dl->sdl_nlen == namelen && !strncmp(name, dl->sdl_data, namelen)) {
      iface = (struct iface *)malloc(sizeof *iface);
      if (iface == NULL) {
        fprintf(stderr, "iface_Create: malloc: %s\n", strerror(errno));
	free(buf);
        return NULL;
      }
      iface->name = strdup(name);
      iface->descr = NULL;
      iface->index = ifm->ifm_index;
      iface->flags = ifm->ifm_flags;
      iface->mtu = 0;
      iface->addrs = 0;
      iface->addr = NULL;
    }
    ptr += ifm->ifm_msglen;				/* First ifa_msghdr */
    for (; ptr < end; ptr += ifam->ifam_msglen) {
      ifam = (struct ifa_msghdr *)ptr;			/* Next if address */

      if (ifam->ifam_type != RTM_NEWADDR)		/* finished this if */
        break;

      if (iface != NULL && ifam->ifam_addrs & RTA_IFA) {
        /* Found a configured interface ! */
        iface_ParseHdr(ifam, sa);

        if (sa[RTAX_IFA] && (sa[RTAX_IFA]->sa_family == AF_INET
#ifndef NOINET6
                             || sa[RTAX_IFA]->sa_family == AF_INET6
#endif
                             )) {
          /* Record the address */

          addr = (struct iface_addr *)
            realloc(iface->addr, (iface->addrs + 1) * sizeof iface->addr[0]);
          if (addr == NULL)
            break;
          iface->addr = addr;

          addr += iface->addrs;
          iface->addrs++;

          ncprange_setsa(&addr->ifa, sa[RTAX_IFA], sa[RTAX_NETMASK]);
          if (sa[RTAX_BRD])
            ncpaddr_setsa(&addr->peer, sa[RTAX_BRD]);
          else
            ncpaddr_init(&addr->peer);
        }
      }
    }
  }

  free(buf);

  return iface;
}