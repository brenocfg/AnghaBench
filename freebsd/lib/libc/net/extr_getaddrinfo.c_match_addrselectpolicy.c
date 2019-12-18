#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct sockaddr_in6 {int sin6_family; int sin6_len; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_addrpolicy {TYPE_2__ addr; TYPE_1__ addrmask; } ;
struct policyqueue {struct in6_addrpolicy pc_policy; } ;
struct policyhead {int dummy; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 struct policyqueue* TAILQ_FIRST (struct policyhead*) ; 
 struct policyqueue* TAILQ_NEXT (struct policyqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _map_v4v6_address (char*,char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pc_entry ; 

__attribute__((used)) static struct policyqueue *
match_addrselectpolicy(struct sockaddr *addr, struct policyhead *head)
{
#ifdef INET6
	struct policyqueue *ent, *bestent = NULL;
	struct in6_addrpolicy *pol;
	int matchlen, bestmatchlen = -1;
	u_char *mp, *ep, *k, *p, m;
	struct sockaddr_in6 key;

	switch(addr->sa_family) {
	case AF_INET6:
		key = *(struct sockaddr_in6 *)addr;
		break;
	case AF_INET:
		/* convert the address into IPv4-mapped IPv6 address. */
		memset(&key, 0, sizeof(key));
		key.sin6_family = AF_INET6;
		key.sin6_len = sizeof(key);
		_map_v4v6_address(
		    (char *)&((struct sockaddr_in *)addr)->sin_addr,
		    (char *)&key.sin6_addr);
		break;
	default:
		return(NULL);
	}

	for (ent = TAILQ_FIRST(head); ent; ent = TAILQ_NEXT(ent, pc_entry)) {
		pol = &ent->pc_policy;
		matchlen = 0;

		mp = (u_char *)&pol->addrmask.sin6_addr;
		ep = mp + 16;	/* XXX: scope field? */
		k = (u_char *)&key.sin6_addr;
		p = (u_char *)&pol->addr.sin6_addr;
		for (; mp < ep && *mp; mp++, k++, p++) {
			m = *mp;
			if ((*k & m) != *p)
				goto next; /* not match */
			if (m == 0xff) /* short cut for a typical case */
				matchlen += 8;
			else {
				while (m >= 0x80) {
					matchlen++;
					m <<= 1;
				}
			}
		}

		/* matched.  check if this is better than the current best. */
		if (matchlen > bestmatchlen) {
			bestent = ent;
			bestmatchlen = matchlen;
		}

	  next:
		continue;
	}

	return(bestent);
#else
	return(NULL);
#endif

}