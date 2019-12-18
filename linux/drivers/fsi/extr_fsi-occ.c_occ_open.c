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
typedef  int /*<<< orphan*/  u8 ;
struct occ_client {int /*<<< orphan*/  lock; struct occ* occ; int /*<<< orphan*/ * buffer; } ;
struct occ {int dummy; } ;
struct miscdevice {int /*<<< orphan*/  lock; struct occ* occ; int /*<<< orphan*/ * buffer; } ;
struct inode {int dummy; } ;
struct file {struct occ_client* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OCC_CMD_DATA_BYTES ; 
 scalar_t__ OCC_RESP_DATA_BYTES ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct occ_client*) ; 
 struct occ_client* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct occ* to_occ (struct occ_client*) ; 

__attribute__((used)) static int occ_open(struct inode *inode, struct file *file)
{
	struct occ_client *client = kzalloc(sizeof(*client), GFP_KERNEL);
	struct miscdevice *mdev = file->private_data;
	struct occ *occ = to_occ(mdev);

	if (!client)
		return -ENOMEM;

	client->buffer = (u8 *)__get_free_page(GFP_KERNEL);
	if (!client->buffer) {
		kfree(client);
		return -ENOMEM;
	}

	client->occ = occ;
	mutex_init(&client->lock);
	file->private_data = client;

	/* We allocate a 1-page buffer, make sure it all fits */
	BUILD_BUG_ON((OCC_CMD_DATA_BYTES + 3) > PAGE_SIZE);
	BUILD_BUG_ON((OCC_RESP_DATA_BYTES + 7) > PAGE_SIZE);

	return 0;
}