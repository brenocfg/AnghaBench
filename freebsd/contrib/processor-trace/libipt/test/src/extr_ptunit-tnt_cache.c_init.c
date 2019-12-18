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
typedef  int /*<<< orphan*/  tnt_cache ;
struct ptunit_result {int dummy; } ;
struct pt_tnt_cache {int /*<<< orphan*/  index; int /*<<< orphan*/  tnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_tnt_cache*,int,int) ; 
 int /*<<< orphan*/  pt_tnt_cache_init (struct pt_tnt_cache*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result init(void)
{
	struct pt_tnt_cache tnt_cache;

	memset(&tnt_cache, 0xcd, sizeof(tnt_cache));

	pt_tnt_cache_init(&tnt_cache);

	ptu_uint_eq(tnt_cache.tnt, 0ull);
	ptu_uint_eq(tnt_cache.index, 0ull);

	return ptu_passed();
}