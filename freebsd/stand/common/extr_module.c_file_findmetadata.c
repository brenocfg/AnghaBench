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
struct preloaded_file {struct file_metadata* f_metadata; } ;
struct file_metadata {int md_type; struct file_metadata* md_next; } ;

/* Variables and functions */

struct file_metadata *
file_findmetadata(struct preloaded_file *fp, int type)
{
	struct file_metadata *md;

	for (md = fp->f_metadata; md != NULL; md = md->md_next)
		if (md->md_type == type)
			break;
	return(md);
}