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
struct _buf {scalar_t__ mounted; } ;

/* Variables and functions */
 int kobj_read_file_loader (struct _buf*,char*,unsigned int,unsigned int) ; 
 int kobj_read_file_vnode (struct _buf*,char*,unsigned int,unsigned int) ; 

int
kobj_read_file(struct _buf *file, char *buf, unsigned size, unsigned off)
{

	if (file->mounted)
		return (kobj_read_file_vnode(file, buf, size, off));
	else
		return (kobj_read_file_loader(file, buf, size, off));
}