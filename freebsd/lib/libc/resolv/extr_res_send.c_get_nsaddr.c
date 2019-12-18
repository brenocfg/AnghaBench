#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  TYPE_3__* res_state ;
struct TYPE_10__ {TYPE_1__* ext; } ;
struct TYPE_9__ {TYPE_2__* nsaddr_list; } ;
struct TYPE_8__ {int /*<<< orphan*/  sin_family; } ;
struct TYPE_7__ {int /*<<< orphan*/ * nsaddrs; } ;

/* Variables and functions */
 TYPE_5__ EXT (TYPE_3__*) ; 

__attribute__((used)) static struct sockaddr *
get_nsaddr(res_state statp, size_t n)
{

	if (!statp->nsaddr_list[n].sin_family && EXT(statp).ext) {
		/*
		 * - EXT(statp).ext->nsaddrs[n] holds an address that is larger
		 *   than struct sockaddr, and
		 * - user code did not update statp->nsaddr_list[n].
		 */
		return (struct sockaddr *)(void *)&EXT(statp).ext->nsaddrs[n];
	} else {
		/*
		 * - user code updated statp->nsaddr_list[n], or
		 * - statp->nsaddr_list[n] has the same content as
		 *   EXT(statp).ext->nsaddrs[n].
		 */
		return (struct sockaddr *)(void *)&statp->nsaddr_list[n];
	}
}