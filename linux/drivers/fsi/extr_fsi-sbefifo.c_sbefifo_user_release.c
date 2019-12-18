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
struct sbefifo_user {scalar_t__ cmd_page; } ;
struct inode {int dummy; } ;
struct file {struct sbefifo_user* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct sbefifo_user*) ; 
 int /*<<< orphan*/  sbefifo_release_command (struct sbefifo_user*) ; 

__attribute__((used)) static int sbefifo_user_release(struct inode *inode, struct file *file)
{
	struct sbefifo_user *user = file->private_data;

	if (!user)
		return -EINVAL;

	sbefifo_release_command(user);
	free_page((unsigned long)user->cmd_page);
	kfree(user);

	return 0;
}