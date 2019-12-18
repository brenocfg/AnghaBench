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
struct file_priv {TYPE_1__* chip; } ;
struct file {struct file_priv* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct file_priv*) ; 
 int /*<<< orphan*/  tpm_common_release (struct file*,struct file_priv*) ; 

__attribute__((used)) static int tpm_release(struct inode *inode, struct file *file)
{
	struct file_priv *priv = file->private_data;

	tpm_common_release(file, priv);
	clear_bit(0, &priv->chip->is_open);
	kfree(priv);

	return 0;
}