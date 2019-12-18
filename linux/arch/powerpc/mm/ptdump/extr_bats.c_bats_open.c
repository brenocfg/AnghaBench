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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PPC_BOOK3S_601 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bats_show_601 ; 
 int /*<<< orphan*/  bats_show_603 ; 
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bats_open(struct inode *inode, struct file *file)
{
	if (IS_ENABLED(CONFIG_PPC_BOOK3S_601))
		return single_open(file, bats_show_601, NULL);

	return single_open(file, bats_show_603, NULL);
}