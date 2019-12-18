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
struct occ_client {scalar_t__ buffer; } ;
struct inode {int dummy; } ;
struct file {struct occ_client* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct occ_client*) ; 

__attribute__((used)) static int occ_release(struct inode *inode, struct file *file)
{
	struct occ_client *client = file->private_data;

	free_page((unsigned long)client->buffer);
	kfree(client);

	return 0;
}