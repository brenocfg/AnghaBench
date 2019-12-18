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
struct pt_mapped_section {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_msec_init (struct pt_mapped_section*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  pt_msec_unmap (struct pt_mapped_section*,int) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result unmap(void)
{
	struct pt_mapped_section msec;
	uint64_t offset;

	pt_msec_init(&msec, NULL, NULL, 0x2000ull, 0x100ull, 0x1000ull);

	offset = pt_msec_unmap(&msec, 0x3000);
	ptu_uint_eq(offset, 0x1100);

	return ptu_passed();
}