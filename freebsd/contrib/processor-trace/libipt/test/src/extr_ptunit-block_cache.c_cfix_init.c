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
struct bcache_fixture {int /*<<< orphan*/ * bcache; int /*<<< orphan*/  thrd; } ;

/* Variables and functions */
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptunit_thrd_init ; 

__attribute__((used)) static struct ptunit_result cfix_init(struct bcache_fixture *bfix)
{
	ptu_test(ptunit_thrd_init, &bfix->thrd);

	bfix->bcache = NULL;

	return ptu_passed();
}