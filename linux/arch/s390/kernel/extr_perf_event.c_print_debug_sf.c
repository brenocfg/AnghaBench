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
struct hws_qsi_info_block {int /*<<< orphan*/  dear; int /*<<< orphan*/  tear; int /*<<< orphan*/  dsdes; int /*<<< orphan*/  cd; int /*<<< orphan*/  ed; scalar_t__ ad; int /*<<< orphan*/  bsdes; int /*<<< orphan*/  cs; int /*<<< orphan*/  es; scalar_t__ as; int /*<<< orphan*/  cpu_speed; int /*<<< orphan*/  max_sampl_rate; int /*<<< orphan*/  min_sampl_rate; } ;
typedef  int /*<<< orphan*/  si ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct hws_qsi_info_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ qsi (struct hws_qsi_info_block*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void print_debug_sf(void)
{
	struct hws_qsi_info_block si;
	int cpu = smp_processor_id();

	memset(&si, 0, sizeof(si));
	if (qsi(&si))
		return;

	pr_info("CPU[%i] CPUM_SF: basic=%i diag=%i min=%lu max=%lu cpu_speed=%u\n",
		cpu, si.as, si.ad, si.min_sampl_rate, si.max_sampl_rate,
		si.cpu_speed);

	if (si.as)
		pr_info("CPU[%i] CPUM_SF: Basic-sampling: a=%i e=%i c=%i"
			" bsdes=%i tear=%016lx dear=%016lx\n", cpu,
			si.as, si.es, si.cs, si.bsdes, si.tear, si.dear);
	if (si.ad)
		pr_info("CPU[%i] CPUM_SF: Diagnostic-sampling: a=%i e=%i c=%i"
			" dsdes=%i tear=%016lx dear=%016lx\n", cpu,
			si.ad, si.ed, si.cd, si.dsdes, si.tear, si.dear);
}