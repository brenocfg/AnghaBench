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
struct pt_tnt_cache {unsigned long long tnt; unsigned long long index; } ;

/* Variables and functions */
 int pt_tnt_cache_query (struct pt_tnt_cache*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ptunit_result query_not_taken(void)
{
	struct pt_tnt_cache tnt_cache;
	int status;

	tnt_cache.tnt = 0ull;
	tnt_cache.index = 1ull;

	status = pt_tnt_cache_query(&tnt_cache);
	ptu_int_eq(status, 0);
	ptu_uint_eq(tnt_cache.index, 0);

	return ptu_passed();
}