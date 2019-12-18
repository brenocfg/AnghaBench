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
struct s3c_freq {int /*<<< orphan*/  armclk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  hclk; int /*<<< orphan*/  fclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_max(struct seq_file *seq, struct s3c_freq *f)
{
	seq_printf(seq, "MAX: F=%lu, H=%lu, P=%lu, A=%lu\n",
		   f->fclk, f->hclk, f->pclk, f->armclk);
}