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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct seq_file {scalar_t__ private; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int seq_release (struct inode*,struct file*) ; 

__attribute__((used)) static int tpm_bios_measurements_release(struct inode *inode,
					 struct file *file)
{
	struct seq_file *seq = (struct seq_file *)file->private_data;
	struct tpm_chip *chip = (struct tpm_chip *)seq->private;

	put_device(&chip->dev);

	return seq_release(inode, file);
}