#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ifaddrs; int /*<<< orphan*/ * proc; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeifaddrs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
internal_destroy(isc_interfaceiter_t *iter) {

#ifdef __linux
	if (iter->proc != NULL)
		fclose(iter->proc);
	iter->proc = NULL;
#endif
	if (iter->ifaddrs)
		freeifaddrs(iter->ifaddrs);
	iter->ifaddrs = NULL;
}