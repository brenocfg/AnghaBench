#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int sin_family; } ;
union res_sockaddr_union {TYPE_8__ sin6; TYPE_8__ sin; } ;
typedef  TYPE_4__* res_state ;
struct TYPE_13__ {int /*<<< orphan*/  sin_family; } ;
struct TYPE_10__ {TYPE_1__* ext; scalar_t__ nscount; } ;
struct TYPE_11__ {TYPE_2__ _ext; } ;
struct TYPE_12__ {int nscount; TYPE_7__* nsaddr_list; TYPE_3__ _u; } ;
struct TYPE_9__ {TYPE_7__* nsaddrs; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int MAXNS ; 
 int /*<<< orphan*/  memcpy (TYPE_7__*,TYPE_8__*,size_t) ; 
 int /*<<< orphan*/  res_nclose (TYPE_4__*) ; 

void
res_setservers(res_state statp, const union res_sockaddr_union *set, int cnt) {
	int i, nserv;
	size_t size;

	/* close open servers */
	res_nclose(statp);

	/* cause rtt times to be forgotten */
	statp->_u._ext.nscount = 0;

	nserv = 0;
	for (i = 0; i < cnt && nserv < MAXNS; i++) {
		switch (set->sin.sin_family) {
		case AF_INET:
			size = sizeof(set->sin);
			if (statp->_u._ext.ext)
				memcpy(&statp->_u._ext.ext->nsaddrs[nserv],
					&set->sin, size);
			if (size <= sizeof(statp->nsaddr_list[nserv]))
				memcpy(&statp->nsaddr_list[nserv],
					&set->sin, size);
			else
				statp->nsaddr_list[nserv].sin_family = 0;
			nserv++;
			break;

#ifdef HAS_INET6_STRUCTS
		case AF_INET6:
			size = sizeof(set->sin6);
			if (statp->_u._ext.ext)
				memcpy(&statp->_u._ext.ext->nsaddrs[nserv],
					&set->sin6, size);
			if (size <= sizeof(statp->nsaddr_list[nserv]))
				memcpy(&statp->nsaddr_list[nserv],
					&set->sin6, size);
			else
				statp->nsaddr_list[nserv].sin_family = 0;
			nserv++;
			break;
#endif

		default:
			break;
		}
		set++;
	}
	statp->nscount = nserv;
	
}