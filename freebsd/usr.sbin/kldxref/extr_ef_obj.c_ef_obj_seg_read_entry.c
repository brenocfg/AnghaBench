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
typedef  int /*<<< orphan*/  elf_file_t ;
typedef  int /*<<< orphan*/  Elf_Off ;

/* Variables and functions */
 int ef_obj_seg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,void*) ; 
 int errno ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t) ; 

__attribute__((used)) static int
ef_obj_seg_read_entry(elf_file_t ef, Elf_Off offset, size_t len, void **ptr)
{
	int error;

	*ptr = malloc(len);
	if (*ptr == NULL)
		return (errno);
	error = ef_obj_seg_read(ef, offset, len, *ptr);
	if (error != 0)
		free(*ptr);
	return (error);
}