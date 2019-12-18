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
struct pt_cpu {int vendor; int /*<<< orphan*/  stepping; int /*<<< orphan*/  model; int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcv_intel ; 
 int pt_cpu_parse (struct pt_cpu*,char*) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_uint_eq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ptunit_result cpu_valid(void)
{
	struct pt_cpu cpu;
	int error;

	error = pt_cpu_parse(&cpu, "6/44/2");
	ptu_int_eq(error, 0);
	ptu_int_eq(cpu.vendor, pcv_intel);
	ptu_uint_eq(cpu.family, 6);
	ptu_uint_eq(cpu.model, 44);
	ptu_uint_eq(cpu.stepping, 2);

	error = pt_cpu_parse(&cpu, "0xf/0x2c/0xf");
	ptu_int_eq(error, 0);
	ptu_int_eq(cpu.vendor, pcv_intel);
	ptu_uint_eq(cpu.family, 0xf);
	ptu_uint_eq(cpu.model, 0x2c);
	ptu_uint_eq(cpu.stepping, 0xf);

	error = pt_cpu_parse(&cpu, "022/054/017");
	ptu_int_eq(error, 0);
	ptu_int_eq(cpu.vendor, pcv_intel);
	ptu_uint_eq(cpu.family, 022);
	ptu_uint_eq(cpu.model, 054);
	ptu_uint_eq(cpu.stepping, 017);

	error = pt_cpu_parse(&cpu, "6/44");
	ptu_int_eq(error, 0);
	ptu_int_eq(cpu.vendor, pcv_intel);
	ptu_uint_eq(cpu.family, 6);
	ptu_uint_eq(cpu.model, 44);
	ptu_uint_eq(cpu.stepping, 0);

	return ptu_passed();
}