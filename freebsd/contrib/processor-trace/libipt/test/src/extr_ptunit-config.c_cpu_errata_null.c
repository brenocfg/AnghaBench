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
struct pt_errata {int dummy; } ;
struct pt_cpu {int dummy; } ;

/* Variables and functions */
 int pt_cpu_errata (struct pt_errata*,struct pt_cpu*) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result cpu_errata_null(void)
{
	struct pt_errata errata;
	struct pt_cpu cpu;
	int errcode;

	errcode = pt_cpu_errata(&errata, NULL);
	ptu_int_eq(errcode, -pte_invalid);

	errcode = pt_cpu_errata(NULL, &cpu);
	ptu_int_eq(errcode, -pte_invalid);

	return ptu_passed();
}