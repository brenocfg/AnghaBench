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
struct seq_file {int dummy; } ;
struct blkcg {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkcg_policy_iocost ; 
 int /*<<< orphan*/  blkcg_print_blkgs (struct seq_file*,struct blkcg*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct blkcg* css_to_blkcg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_qos_prfill ; 
 TYPE_1__* seq_cft (struct seq_file*) ; 
 int /*<<< orphan*/  seq_css (struct seq_file*) ; 

__attribute__((used)) static int ioc_qos_show(struct seq_file *sf, void *v)
{
	struct blkcg *blkcg = css_to_blkcg(seq_css(sf));

	blkcg_print_blkgs(sf, blkcg, ioc_qos_prfill,
			  &blkcg_policy_iocost, seq_cft(sf)->private, false);
	return 0;
}