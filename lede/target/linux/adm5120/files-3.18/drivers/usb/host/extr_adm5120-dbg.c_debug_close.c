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
struct file {struct debug_buffer* private_data; } ;
struct debug_buffer {scalar_t__ page; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct debug_buffer*) ; 

__attribute__((used)) static int debug_close(struct inode *inode, struct file *file)
{
	struct debug_buffer *buf = file->private_data;

	if (buf) {
		if (buf->page)
			free_page((unsigned long)buf->page);
		kfree(buf);
	}

	return 0;
}