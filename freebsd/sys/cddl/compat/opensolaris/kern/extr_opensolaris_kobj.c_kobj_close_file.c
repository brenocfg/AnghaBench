#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct _buf {int /*<<< orphan*/  ptr; scalar_t__ mounted; } ;
struct TYPE_3__ {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREAD ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  kmem_free (struct _buf*,int) ; 
 int /*<<< orphan*/  vn_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

void
kobj_close_file(struct _buf *file)
{

	if (file->mounted)
		vn_close(file->ptr, FREAD, curthread->td_ucred, curthread);
	kmem_free(file, sizeof(*file));
}