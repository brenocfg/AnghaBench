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
struct inode {struct drbd_connection* i_private; } ;
struct file {int dummy; } ;
struct drbd_connection {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  connection_oldest_requests_show ; 
 int /*<<< orphan*/  drbd_destroy_connection ; 
 int drbd_single_open (struct file*,int /*<<< orphan*/ ,struct drbd_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int connection_oldest_requests_open(struct inode *inode, struct file *file)
{
	struct drbd_connection *connection = inode->i_private;
	return drbd_single_open(file, connection_oldest_requests_show, connection,
				&connection->kref, drbd_destroy_connection);
}