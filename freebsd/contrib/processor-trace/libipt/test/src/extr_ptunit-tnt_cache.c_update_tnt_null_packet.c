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
 int pt_tnt_cache_update_tnt (struct pt_tnt_cache*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (unsigned long long,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result update_tnt_null_packet(void)
{
	struct pt_tnt_cache tnt_cache;
	int errcode;

	tnt_cache.tnt = 42ull;
	tnt_cache.index = 12ull;

	errcode = pt_tnt_cache_update_tnt(&tnt_cache, NULL, NULL);
	ptu_int_eq(errcode, -pte_invalid);
	ptu_uint_eq(tnt_cache.tnt, 42ull);
	ptu_uint_eq(tnt_cache.index, 12ull);

	return ptu_passed();
}