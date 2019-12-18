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
struct seq_file {int dummy; } ;
struct hws_qsi_info_block {int /*<<< orphan*/  dsdes; scalar_t__ ad; int /*<<< orphan*/  bsdes; scalar_t__ as; int /*<<< orphan*/  cpu_speed; int /*<<< orphan*/  max_sampl_rate; int /*<<< orphan*/  min_sampl_rate; } ;
typedef  int /*<<< orphan*/  si ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct hws_qsi_info_block*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qsi (struct hws_qsi_info_block*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void sl_print_sampling(struct seq_file *m)
{
	struct hws_qsi_info_block si;

	memset(&si, 0, sizeof(si));
	if (qsi(&si))
		return;

	if (!si.as && !si.ad)
		return;

	seq_printf(m, "CPU-MF: Sampling facility: min_rate=%lu max_rate=%lu"
		   " cpu_speed=%u\n", si.min_sampl_rate, si.max_sampl_rate,
		   si.cpu_speed);
	if (si.as)
		seq_printf(m, "CPU-MF: Sampling facility: mode=basic"
			   " sample_size=%u\n", si.bsdes);
	if (si.ad)
		seq_printf(m, "CPU-MF: Sampling facility: mode=diagnostic"
			   " sample_size=%u\n", si.dsdes);
}