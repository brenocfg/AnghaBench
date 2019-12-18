#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct hostent_data {char* hostbuf; char** host_aliases; char** h_addr_ptrs; } ;
struct hostent {char* h_name; char** h_aliases; char** h_addr_list; int h_length; } ;
typedef  TYPE_1__* res_state ;
struct TYPE_11__ {int /*<<< orphan*/  qdcount; int /*<<< orphan*/  ancount; } ;
struct TYPE_10__ {int /*<<< orphan*/ * buf; TYPE_3__ hdr; } ;
typedef  TYPE_2__ querybuf ;
typedef  int /*<<< orphan*/  align ;
struct TYPE_9__ {int options; scalar_t__ nsort; } ;
typedef  TYPE_3__ HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  AskedForGot ; 
 int /*<<< orphan*/  BOUNDED_INCR (scalar_t__) ; 
 int /*<<< orphan*/  BOUNDS_CHECK (int /*<<< orphan*/  const*,int) ; 
 int C_IN ; 
 scalar_t__ HFIXEDSZ ; 
 int INT16SZ ; 
 int INT32SZ ; 
 int LOG_AUTH ; 
 int LOG_NOTICE ; 
 int MAXDNAME ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  NETDB_SUCCESS ; 
 int /*<<< orphan*/  NO_RECOVERY ; 
 scalar_t__ QFIXEDSZ ; 
 int /*<<< orphan*/  RES_SET_H_ERRNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int RES_USE_INET6 ; 
#define  T_A 130 
#define  T_AAAA 129 
 int T_CNAME ; 
#define  T_PTR 128 
 int T_SIG ; 
 int _MAXADDRS ; 
 int _MAXALIASES ; 
 int _dns_ttl_ ; 
 int _getlong (int /*<<< orphan*/  const*) ; 
 int _getshort (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _map_v4v6_hostent (struct hostent*,char**,char*) ; 
 int /*<<< orphan*/  addrsort (char**,int,TYPE_1__*) ; 
 int /*<<< orphan*/  dbg_printf (char*,int,TYPE_1__*) ; 
 int dn_expand (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,int) ; 
 int ns_t_dname ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_class (int) ; 
 int /*<<< orphan*/  p_type (int) ; 
 int res_dnok (char*) ; 
 int res_hnok (char*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int stub1 (char const*) ; 
 int stub2 (char const*) ; 
 int stub3 (char const*) ; 
 int /*<<< orphan*/  syslog (int,char*,char const*,char*,...) ; 

__attribute__((used)) static int
gethostanswer(const querybuf *answer, int anslen, const char *qname, int qtype,
    struct hostent *he, struct hostent_data *hed, res_state statp)
{
	const HEADER *hp;
	const u_char *cp;
	int n;
	const u_char *eom, *erdata;
	char *bp, *ep, **ap, **hap;
	int type, class, ancount, qdcount;
	int haveanswer, had_error;
	int toobig = 0;
	char tbuf[MAXDNAME];
	const char *tname;
	int (*name_ok)(const char *);

	tname = qname;
	he->h_name = NULL;
	eom = answer->buf + anslen;
	switch (qtype) {
	case T_A:
	case T_AAAA:
		name_ok = res_hnok;
		break;
	case T_PTR:
		name_ok = res_dnok;
		break;
	default:
		RES_SET_H_ERRNO(statp, NO_RECOVERY);
		return (-1);	/* XXX should be abort(); */
	}
	/*
	 * find first satisfactory answer
	 */
	hp = &answer->hdr;
	ancount = ntohs(hp->ancount);
	qdcount = ntohs(hp->qdcount);
	bp = hed->hostbuf;
	ep = hed->hostbuf + sizeof hed->hostbuf;
	cp = answer->buf;
	BOUNDED_INCR(HFIXEDSZ);
	if (qdcount != 1) {
		RES_SET_H_ERRNO(statp, NO_RECOVERY);
		return (-1);
	}
	n = dn_expand(answer->buf, eom, cp, bp, ep - bp);
	if ((n < 0) || !(*name_ok)(bp)) {
		RES_SET_H_ERRNO(statp, NO_RECOVERY);
		return (-1);
	}
	BOUNDED_INCR(n + QFIXEDSZ);
	if (qtype == T_A || qtype == T_AAAA) {
		/* res_send() has already verified that the query name is the
		 * same as the one we sent; this just gets the expanded name
		 * (i.e., with the succeeding search-domain tacked on).
		 */
		n = strlen(bp) + 1;		/* for the \0 */
		if (n >= MAXHOSTNAMELEN) {
			RES_SET_H_ERRNO(statp, NO_RECOVERY);
			return (-1);
		}
		he->h_name = bp;
		bp += n;
		/* The qname can be abbreviated, but h_name is now absolute. */
		qname = he->h_name;
	}
	ap = hed->host_aliases;
	*ap = NULL;
	he->h_aliases = hed->host_aliases;
	hap = hed->h_addr_ptrs;
	*hap = NULL;
	he->h_addr_list = hed->h_addr_ptrs;
	haveanswer = 0;
	had_error = 0;
	_dns_ttl_ = -1;
	while (ancount-- > 0 && cp < eom && !had_error) {
		n = dn_expand(answer->buf, eom, cp, bp, ep - bp);
		if ((n < 0) || !(*name_ok)(bp)) {
			had_error++;
			continue;
		}
		cp += n;			/* name */
		BOUNDS_CHECK(cp, 3 * INT16SZ + INT32SZ);
		type = _getshort(cp);
 		cp += INT16SZ;			/* type */
		class = _getshort(cp);
 		cp += INT16SZ;			/* class */
		if (qtype == T_A  && type == T_A)
			_dns_ttl_ = _getlong(cp);
		cp += INT32SZ;			/* TTL */
		n = _getshort(cp);
		cp += INT16SZ;			/* len */
		BOUNDS_CHECK(cp, n);
		erdata = cp + n;
		if (class != C_IN) {
			/* XXX - debug? syslog? */
			cp += n;
			continue;		/* XXX - had_error++ ? */
		}
		if ((qtype == T_A || qtype == T_AAAA) && type == T_CNAME) {
			if (ap >= &hed->host_aliases[_MAXALIASES-1])
				continue;
			n = dn_expand(answer->buf, eom, cp, tbuf, sizeof tbuf);
			if ((n < 0) || !(*name_ok)(tbuf)) {
				had_error++;
				continue;
			}
			cp += n;
			if (cp != erdata) {
				RES_SET_H_ERRNO(statp, NO_RECOVERY);
				return (-1);
			}
			/* Store alias. */
			*ap++ = bp;
			n = strlen(bp) + 1;	/* for the \0 */
			if (n >= MAXHOSTNAMELEN) {
				had_error++;
				continue;
			}
			bp += n;
			/* Get canonical name. */
			n = strlen(tbuf) + 1;	/* for the \0 */
			if (n > ep - bp || n >= MAXHOSTNAMELEN) {
				had_error++;
				continue;
			}
			strcpy(bp, tbuf);
			he->h_name = bp;
			bp += n;
			continue;
		}
		if (qtype == T_PTR && type == T_CNAME) {
			n = dn_expand(answer->buf, eom, cp, tbuf, sizeof tbuf);
			if (n < 0 || !res_dnok(tbuf)) {
				had_error++;
				continue;
			}
			cp += n;
			if (cp != erdata) {
				RES_SET_H_ERRNO(statp, NO_RECOVERY);
				return (-1);
			}
			/* Get canonical name. */
			n = strlen(tbuf) + 1;	/* for the \0 */
			if (n > ep - bp || n >= MAXHOSTNAMELEN) {
				had_error++;
				continue;
			}
			strcpy(bp, tbuf);
			tname = bp;
			bp += n;
			continue;
		}
		if (type != qtype) {
			if (type != T_SIG && type != ns_t_dname)
				syslog(LOG_NOTICE|LOG_AUTH,
	"gethostby*.gethostanswer: asked for \"%s %s %s\", got type \"%s\"",
				       qname, p_class(C_IN), p_type(qtype),
				       p_type(type));
			cp += n;
			continue;		/* XXX - had_error++ ? */
		}
		switch (type) {
		case T_PTR:
			if (strcasecmp(tname, bp) != 0) {
				syslog(LOG_NOTICE|LOG_AUTH,
				       AskedForGot, qname, bp);
				cp += n;
				continue;	/* XXX - had_error++ ? */
			}
			n = dn_expand(answer->buf, eom, cp, bp, ep - bp);
			if ((n < 0) || !res_hnok(bp)) {
				had_error++;
				break;
			}
#if MULTI_PTRS_ARE_ALIASES
			cp += n;
			if (cp != erdata) {
				RES_SET_H_ERRNO(statp, NO_RECOVERY);
				return (-1);
			}
			if (!haveanswer)
				he->h_name = bp;
			else if (ap < &hed->host_aliases[_MAXALIASES-1])
				*ap++ = bp;
			else
				n = -1;
			if (n != -1) {
				n = strlen(bp) + 1;	/* for the \0 */
				if (n >= MAXHOSTNAMELEN) {
					had_error++;
					break;
				}
				bp += n;
			}
			break;
#else
			he->h_name = bp;
			if (statp->options & RES_USE_INET6) {
				n = strlen(bp) + 1;	/* for the \0 */
				if (n >= MAXHOSTNAMELEN) {
					had_error++;
					break;
				}
				bp += n;
				_map_v4v6_hostent(he, &bp, ep);
			}
			RES_SET_H_ERRNO(statp, NETDB_SUCCESS);
			return (0);
#endif
		case T_A:
		case T_AAAA:
			if (strcasecmp(he->h_name, bp) != 0) {
				syslog(LOG_NOTICE|LOG_AUTH,
				       AskedForGot, he->h_name, bp);
				cp += n;
				continue;	/* XXX - had_error++ ? */
			}
			if (n != he->h_length) {
				cp += n;
				continue;
			}
			if (!haveanswer) {
				int nn;

				he->h_name = bp;
				nn = strlen(bp) + 1;	/* for the \0 */
				bp += nn;
			}

			bp += sizeof(align) - ((u_long)bp % sizeof(align));

			if (bp + n >= ep) {
				dbg_printf("size (%d) too big\n", n, statp);
				had_error++;
				continue;
			}
			if (hap >= &hed->h_addr_ptrs[_MAXADDRS-1]) {
				if (!toobig++)
					dbg_printf("Too many addresses (%d)\n",
						_MAXADDRS, statp);
				cp += n;
				continue;
			}
			memcpy(*hap++ = bp, cp, n);
			bp += n;
			cp += n;
			if (cp != erdata) {
				RES_SET_H_ERRNO(statp, NO_RECOVERY);
				return (-1);
			}
			break;
		default:
			dbg_printf("Impossible condition (type=%d)\n", type,
			    statp);
			RES_SET_H_ERRNO(statp, NO_RECOVERY);
			return (-1);
			/* BIND has abort() here, too risky on bad data */
		}
		if (!had_error)
			haveanswer++;
	}
	if (haveanswer) {
		*ap = NULL;
		*hap = NULL;
# if defined(RESOLVSORT)
		/*
		 * Note: we sort even if host can take only one address
		 * in its return structures - should give it the "best"
		 * address in that case, not some random one
		 */
		if (statp->nsort && haveanswer > 1 && qtype == T_A)
			addrsort(hed->h_addr_ptrs, haveanswer, statp);
# endif /*RESOLVSORT*/
		if (!he->h_name) {
			n = strlen(qname) + 1;	/* for the \0 */
			if (n > ep - bp || n >= MAXHOSTNAMELEN)
				goto no_recovery;
			strcpy(bp, qname);
			he->h_name = bp;
			bp += n;
		}
		if (statp->options & RES_USE_INET6)
			_map_v4v6_hostent(he, &bp, ep);
		RES_SET_H_ERRNO(statp, NETDB_SUCCESS);
		return (0);
	}
 no_recovery:
	RES_SET_H_ERRNO(statp, NO_RECOVERY);
	return (-1);
}