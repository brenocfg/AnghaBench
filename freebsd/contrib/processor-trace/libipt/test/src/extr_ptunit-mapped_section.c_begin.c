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
struct ptunit_result {int dummy; } ;
struct pt_section {int dummy; } ;
struct pt_mapped_section {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_msec_begin (struct pt_mapped_section*) ; 
 int /*<<< orphan*/  pt_msec_init (struct pt_mapped_section*,struct pt_section*,int /*<<< orphan*/ *,int,int,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result begin(void)
{
	struct pt_mapped_section msec;
	struct pt_section sec;
	uint64_t begin;

	pt_msec_init(&msec, &sec, NULL, 0x2000ull, 0x100ull, 0x1000ull);

	begin = pt_msec_begin(&msec);
	ptu_uint_eq(begin, 0x2000);

	return ptu_passed();
}