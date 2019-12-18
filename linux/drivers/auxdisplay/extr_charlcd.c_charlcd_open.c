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
struct file {int f_mode; } ;
struct charlcd_priv {int must_clear; int /*<<< orphan*/  lcd; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  charlcd_available ; 
 int /*<<< orphan*/  charlcd_clear_display (int /*<<< orphan*/ *) ; 
 struct charlcd_priv* charlcd_to_priv (int /*<<< orphan*/ ) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  the_charlcd ; 

__attribute__((used)) static int charlcd_open(struct inode *inode, struct file *file)
{
	struct charlcd_priv *priv = charlcd_to_priv(the_charlcd);
	int ret;

	ret = -EBUSY;
	if (!atomic_dec_and_test(&charlcd_available))
		goto fail;	/* open only once at a time */

	ret = -EPERM;
	if (file->f_mode & FMODE_READ)	/* device is write-only */
		goto fail;

	if (priv->must_clear) {
		charlcd_clear_display(&priv->lcd);
		priv->must_clear = false;
	}
	return nonseekable_open(inode, file);

 fail:
	atomic_inc(&charlcd_available);
	return ret;
}