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
struct file_metadata {size_t md_size; int md_type; struct file_metadata* md_next; int /*<<< orphan*/  md_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ ,size_t) ; 
 struct file_metadata* malloc (int) ; 

void
file_addmetadata(struct preloaded_file *fp, int type, size_t size, void *p)
{
	struct file_metadata	*md;

	md = malloc(sizeof(struct file_metadata) - sizeof(md->md_data) + size);
	if (md != NULL) {
		md->md_size = size;
		md->md_type = type;
		bcopy(p, md->md_data, size);
		md->md_next = fp->f_metadata;
	}
	fp->f_metadata = md;
}