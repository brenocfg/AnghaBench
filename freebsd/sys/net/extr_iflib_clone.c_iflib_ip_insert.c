#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_pseudo_t ;
struct TYPE_4__ {int ip_on_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PSEUDO_LOCK () ; 
 int /*<<< orphan*/  PSEUDO_UNLOCK () ; 
 int /*<<< orphan*/  iflib_pseudos ; 
 int /*<<< orphan*/  ip_list ; 

__attribute__((used)) static void
iflib_ip_insert(if_pseudo_t ip)
{
	PSEUDO_LOCK();
	if (!ip->ip_on_list) {
		LIST_INSERT_HEAD(&iflib_pseudos, ip, ip_list);
		ip->ip_on_list = 1;
	}
	PSEUDO_UNLOCK();
}