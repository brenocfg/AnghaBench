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
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  pt_bcache_alloc (scalar_t__) ; 
 int /*<<< orphan*/  ptu_null (int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result alloc_too_big(struct bcache_fixture *bfix)
{
	bfix->bcache = pt_bcache_alloc(UINT32_MAX + 1ull);
	ptu_null(bfix->bcache);

	return ptu_passed();
}