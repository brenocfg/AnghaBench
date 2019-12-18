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
struct pt_unit {int flags; int /*<<< orphan*/  available; int /*<<< orphan*/  name; int /*<<< orphan*/ * bufptr; int /*<<< orphan*/  present; } ;
struct inode {int dummy; } ;
struct file {int f_mode; struct pt_unit* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EROFS ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PT_BUFSIZE ; 
 int PT_MEDIA ; 
 int PT_REWIND ; 
 int PT_UNITS ; 
 int PT_WRITE_OK ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 struct pt_unit* pt ; 
 int /*<<< orphan*/  pt_identify (struct pt_unit*) ; 
 int /*<<< orphan*/  pt_mutex ; 

__attribute__((used)) static int pt_open(struct inode *inode, struct file *file)
{
	int unit = iminor(inode) & 0x7F;
	struct pt_unit *tape = pt + unit;
	int err;

	mutex_lock(&pt_mutex);
	if (unit >= PT_UNITS || (!tape->present)) {
		mutex_unlock(&pt_mutex);
		return -ENODEV;
	}

	err = -EBUSY;
	if (!atomic_dec_and_test(&tape->available))
		goto out;

	pt_identify(tape);

	err = -ENODEV;
	if (!(tape->flags & PT_MEDIA))
		goto out;

	err = -EROFS;
	if ((!(tape->flags & PT_WRITE_OK)) && (file->f_mode & FMODE_WRITE))
		goto out;

	if (!(iminor(inode) & 128))
		tape->flags |= PT_REWIND;

	err = -ENOMEM;
	tape->bufptr = kmalloc(PT_BUFSIZE, GFP_KERNEL);
	if (tape->bufptr == NULL) {
		printk("%s: buffer allocation failed\n", tape->name);
		goto out;
	}

	file->private_data = tape;
	mutex_unlock(&pt_mutex);
	return 0;

out:
	atomic_inc(&tape->available);
	mutex_unlock(&pt_mutex);
	return err;
}