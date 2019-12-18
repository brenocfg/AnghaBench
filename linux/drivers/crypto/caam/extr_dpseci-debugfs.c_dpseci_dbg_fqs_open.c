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
struct inode {scalar_t__ i_private; } ;
struct file {int dummy; } ;
struct dpaa2_caam_priv {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dpseci_dbg_fqs_show ; 
 int single_open (struct file*,int /*<<< orphan*/ ,struct dpaa2_caam_priv*) ; 

__attribute__((used)) static int dpseci_dbg_fqs_open(struct inode *inode, struct file *file)
{
	int err;
	struct dpaa2_caam_priv *priv;

	priv = (struct dpaa2_caam_priv *)inode->i_private;

	err = single_open(file, dpseci_dbg_fqs_show, priv);
	if (err < 0)
		dev_err(priv->dev, "single_open() failed\n");

	return err;
}