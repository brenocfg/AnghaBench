#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; int cpuid_0x15_eax; int cpuid_0x15_ebx; int mtc_freq; } ;
struct time_fixture {int /*<<< orphan*/  time; int /*<<< orphan*/  tcal; TYPE_1__ config; } ;
struct ptunit_result {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int pt_tcal_fcr_shr ; 
 int /*<<< orphan*/  pt_tcal_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_tcal_set_fcr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pt_time_init (int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result tfix_init(struct time_fixture *tfix)
{
	memset(&tfix->config, 0, sizeof(tfix->config));
	tfix->config.size = sizeof(tfix->config);
	tfix->config.cpuid_0x15_eax = 2;
	tfix->config.cpuid_0x15_ebx = 1;
	tfix->config.mtc_freq = 4;

	pt_tcal_init(&tfix->tcal);
	pt_tcal_set_fcr(&tfix->tcal, 0x2ull << pt_tcal_fcr_shr);

	pt_time_init(&tfix->time);

	return ptu_passed();
}