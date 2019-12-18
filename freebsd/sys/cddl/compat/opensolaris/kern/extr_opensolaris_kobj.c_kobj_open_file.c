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
struct _buf {int /*<<< orphan*/ * ptr; scalar_t__ mounted; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 struct _buf* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (struct _buf*,int) ; 
 int /*<<< orphan*/ * kobj_open_file_loader (char const*) ; 
 int /*<<< orphan*/ * kobj_open_file_vnode (char const*) ; 
 scalar_t__ root_mounted () ; 

struct _buf *
kobj_open_file(const char *file)
{
	struct _buf *out;

	out = kmem_alloc(sizeof(*out), KM_SLEEP);
	out->mounted = root_mounted();
	/*
	 * If root is already mounted we read file using file system,
	 * if not, we use loader.
	 */
	if (out->mounted)
		out->ptr = kobj_open_file_vnode(file);
	else
		out->ptr = kobj_open_file_loader(file);
	if (out->ptr == NULL) {
		kmem_free(out, sizeof(*out));
		return ((struct _buf *)-1);
	}
	return (out);
}