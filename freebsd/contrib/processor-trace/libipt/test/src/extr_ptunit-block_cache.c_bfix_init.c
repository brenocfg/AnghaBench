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
struct bcache_fixture {int /*<<< orphan*/  bcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfix_nentries ; 
 int /*<<< orphan*/  cfix_init ; 
 int /*<<< orphan*/  pt_bcache_alloc (int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptu_test (int /*<<< orphan*/ ,struct bcache_fixture*) ; 

__attribute__((used)) static struct ptunit_result bfix_init(struct bcache_fixture *bfix)
{
	ptu_test(cfix_init, bfix);

	bfix->bcache = pt_bcache_alloc(bfix_nentries);
	ptu_ptr(bfix->bcache);

	return ptu_passed();
}