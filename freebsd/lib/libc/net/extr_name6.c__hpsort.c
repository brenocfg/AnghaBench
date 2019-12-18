#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct hostent {scalar_t__ h_addrtype; int h_length; int /*<<< orphan*/ ** h_addr_list; } ;
typedef  TYPE_6__* res_state ;
struct TYPE_10__ {TYPE_2__* ext; } ;
struct TYPE_11__ {TYPE_3__ _ext; } ;
struct TYPE_13__ {int nsort; TYPE_5__* sort_list; TYPE_4__ _u; } ;
struct TYPE_12__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {TYPE_1__* sort_list; } ;
struct TYPE_8__ {scalar_t__ af; int /*<<< orphan*/  mask; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int MAXADDRS ; 

__attribute__((used)) static struct hostent *
_hpsort(struct hostent *hp, res_state statp)
{
	int i, j, n;
	u_char *ap, *sp, *mp, **pp;
	char t;
	char order[MAXADDRS];
	int nsort = statp->nsort;

	if (hp == NULL || hp->h_addr_list[1] == NULL || nsort == 0)
		return hp;
	for (i = 0; (ap = (u_char *)hp->h_addr_list[i]); i++) {
		for (j = 0; j < nsort; j++) {
#ifdef INET6
			if (statp->_u._ext.ext->sort_list[j].af !=
			    hp->h_addrtype)
				continue;
			sp = (u_char *)&statp->_u._ext.ext->sort_list[j].addr;
			mp = (u_char *)&statp->_u._ext.ext->sort_list[j].mask;
#else
			sp = (u_char *)&statp->sort_list[j].addr;
			mp = (u_char *)&statp->sort_list[j].mask;
#endif
			for (n = 0; n < hp->h_length; n++) {
				if ((ap[n] & mp[n]) != sp[n])
					break;
			}
			if (n == hp->h_length)
				break;
		}
		order[i] = j;
	}
	n = i;
	pp = (u_char **)hp->h_addr_list;
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (order[i] > order[j]) {
				ap = pp[i];
				pp[i] = pp[j];
				pp[j] = ap;
				t = order[i];
				order[i] = order[j];
				order[j] = t;
			}
		}
	}
	return hp;
}