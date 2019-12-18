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
struct pt_tnt_cache {unsigned long long index; } ;

/* Variables and functions */
 int pt_tnt_cache_is_empty (struct pt_tnt_cache*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result is_empty_yes(void)
{
	struct pt_tnt_cache tnt_cache;
	int status;

	tnt_cache.index = 0ull;

	status = pt_tnt_cache_is_empty(&tnt_cache);
	ptu_int_eq(status, 1);

	return ptu_passed();
}