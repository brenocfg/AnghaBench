#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  sin_family; } ;
union res_sockaddr_union {TYPE_7__ sin; TYPE_7__ sin6; } ;
typedef  int u_int16_t ;
typedef  TYPE_5__* res_state ;
struct TYPE_9__ {int sin_family; } ;
struct TYPE_15__ {int sin_family; TYPE_1__ sin; } ;
struct TYPE_11__ {TYPE_2__* ext; } ;
struct TYPE_12__ {TYPE_3__ _ext; } ;
struct TYPE_13__ {int nscount; TYPE_8__* nsaddr_list; TYPE_4__ _u; } ;
struct TYPE_10__ {TYPE_8__* nsaddrs; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  memcpy (TYPE_7__*,TYPE_8__*,size_t) ; 

int
res_getservers(res_state statp, union res_sockaddr_union *set, int cnt) {
	int i;
	size_t size;
	u_int16_t family;

	for (i = 0; i < statp->nscount && i < cnt; i++) {
		if (statp->_u._ext.ext)
			family = statp->_u._ext.ext->nsaddrs[i].sin.sin_family;
		else 
			family = statp->nsaddr_list[i].sin_family;

		switch (family) {
		case AF_INET:
			size = sizeof(set->sin);
			if (statp->_u._ext.ext)
				memcpy(&set->sin,
				       &statp->_u._ext.ext->nsaddrs[i],
				       size);
			else
				memcpy(&set->sin, &statp->nsaddr_list[i],
				       size);
			break;

#ifdef HAS_INET6_STRUCTS
		case AF_INET6:
			size = sizeof(set->sin6);
			if (statp->_u._ext.ext)
				memcpy(&set->sin6,
				       &statp->_u._ext.ext->nsaddrs[i],
				       size);
			else
				memcpy(&set->sin6, &statp->nsaddr_list[i],
				       size);
			break;
#endif

		default:
			set->sin.sin_family = 0;
			break;
		}
		set++;
	}
	return (statp->nscount);
}