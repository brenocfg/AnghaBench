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
struct file {int f_mode; struct apm_user* private_data; } ;
struct apm_user {int writer; int reader; struct apm_user* next; int /*<<< orphan*/  suser; scalar_t__ standbys_read; scalar_t__ suspends_read; scalar_t__ standbys_pending; scalar_t__ suspends_pending; scalar_t__ event_head; scalar_t__ event_tail; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_BIOS_MAGIC ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct apm_user* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct apm_user* user_list ; 
 int /*<<< orphan*/  user_list_lock ; 

__attribute__((used)) static int do_open(struct inode *inode, struct file *filp)
{
	struct apm_user *as;

	as = kmalloc(sizeof(*as), GFP_KERNEL);
	if (as == NULL)
		return -ENOMEM;

	as->magic = APM_BIOS_MAGIC;
	as->event_tail = as->event_head = 0;
	as->suspends_pending = as->standbys_pending = 0;
	as->suspends_read = as->standbys_read = 0;
	/*
	 * XXX - this is a tiny bit broken, when we consider BSD
	 * process accounting. If the device is opened by root, we
	 * instantly flag that we used superuser privs. Who knows,
	 * we might close the device immediately without doing a
	 * privileged operation -- cevans
	 */
	as->suser = capable(CAP_SYS_ADMIN);
	as->writer = (filp->f_mode & FMODE_WRITE) == FMODE_WRITE;
	as->reader = (filp->f_mode & FMODE_READ) == FMODE_READ;
	spin_lock(&user_list_lock);
	as->next = user_list;
	user_list = as;
	spin_unlock(&user_list_lock);
	filp->private_data = as;
	return 0;
}