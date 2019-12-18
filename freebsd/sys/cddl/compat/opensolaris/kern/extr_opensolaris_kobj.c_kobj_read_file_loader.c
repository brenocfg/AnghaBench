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
struct _buf {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  bcopy (char*,char*,unsigned int) ; 
 char* preload_fetch_addr (int /*<<< orphan*/ ) ; 

int
kobj_read_file_loader(struct _buf *file, char *buf, unsigned size, unsigned off)
{
	char *ptr;

	ptr = preload_fetch_addr(file->ptr);
	if (ptr == NULL)
		return (ENOENT);
	bcopy(ptr + off, buf, size);
	return (0);
}