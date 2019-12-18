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
struct subscr_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct subscr_addr*) ; 

void subscr_addr_delete(struct subscr_addr *a)
{
	/*
	 * Note: do NOT free domain_and_port or path because they point to
	 * memory within the allocation of "a".
	 */
	os_free(a);
}