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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_private; } ;

/* Variables and functions */
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  pci_perf_show ; 
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_perf_seq_open(struct inode *inode, struct file *filp)
{
	return single_open(filp, pci_perf_show,
			   file_inode(filp)->i_private);
}