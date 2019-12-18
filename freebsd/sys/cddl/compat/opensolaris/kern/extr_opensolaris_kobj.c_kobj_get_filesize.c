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
typedef  int /*<<< orphan*/  uint64_t ;
struct _buf {scalar_t__ mounted; } ;

/* Variables and functions */
 int kobj_get_filesize_loader (struct _buf*,int /*<<< orphan*/ *) ; 
 int kobj_get_filesize_vnode (struct _buf*,int /*<<< orphan*/ *) ; 

int
kobj_get_filesize(struct _buf *file, uint64_t *size)
{

	if (file->mounted)
		return (kobj_get_filesize_vnode(file, size));
	else
		return (kobj_get_filesize_loader(file, size));
}