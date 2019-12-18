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
struct ptunit_result {int dummy; } ;
struct iscache_fixture {int dummy; } ;

/* Variables and functions */
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result init_fini(struct iscache_fixture *cfix)
{
	(void) cfix;

	/* The actual init and fini calls are in cfix_init() and cfix_fini(). */
	return ptu_passed();
}