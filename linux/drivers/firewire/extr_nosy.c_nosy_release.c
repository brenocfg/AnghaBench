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
struct pcilynx {int /*<<< orphan*/  client_list_lock; } ;
struct inode {int dummy; } ;
struct file {struct client* private_data; } ;
struct client {int /*<<< orphan*/  buffer; int /*<<< orphan*/  link; struct pcilynx* lynx; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct client*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lynx_put (struct pcilynx*) ; 
 int /*<<< orphan*/  packet_buffer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nosy_release(struct inode *inode, struct file *file)
{
	struct client *client = file->private_data;
	struct pcilynx *lynx = client->lynx;

	spin_lock_irq(&lynx->client_list_lock);
	list_del_init(&client->link);
	spin_unlock_irq(&lynx->client_list_lock);

	packet_buffer_destroy(&client->buffer);
	kfree(client);
	lynx_put(lynx);

	return 0;
}