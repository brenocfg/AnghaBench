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
typedef  scalar_t__ uint64_t ;
struct _buf {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MODINFO_SIZE ; 
 void* preload_search_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kobj_get_filesize_loader(struct _buf *file, uint64_t *size)
{
	void *ptr;

	ptr = preload_search_info(file->ptr, MODINFO_SIZE);
	if (ptr == NULL)
		return (ENOENT);
	*size = (uint64_t)*(size_t *)ptr;
	return (0);
}