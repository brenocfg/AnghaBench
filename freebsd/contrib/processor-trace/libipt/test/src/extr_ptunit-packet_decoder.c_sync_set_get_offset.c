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
typedef  int /*<<< orphan*/  uint64_t ;
struct test_fixture {int /*<<< orphan*/  decoder; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int pt_pkt_get_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_pkt_sync_set (int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static struct ptunit_result sync_set_get_offset(struct test_fixture *tfix)
{
	uint64_t offset;
	int errcode;

	errcode = pt_pkt_sync_set(&tfix->decoder, 1ull);
	ptu_int_eq(errcode, 0);

	errcode = pt_pkt_get_offset(&tfix->decoder, &offset);
	ptu_int_eq(errcode, 0);
	ptu_uint_eq(offset, 1ull);

	return ptu_passed();
}