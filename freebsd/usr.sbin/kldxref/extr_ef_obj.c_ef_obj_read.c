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
typedef  int ssize_t ;
typedef  TYPE_1__* elf_file_t ;
struct TYPE_3__ {int /*<<< orphan*/  ef_fd; } ;
typedef  scalar_t__ Elf_Off ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int
ef_obj_read(elf_file_t ef, Elf_Off offset, size_t len, void *dest)
{
	ssize_t r;

	if (offset != (Elf_Off)-1) {
		if (lseek(ef->ef_fd, offset, SEEK_SET) == -1)
			return (EIO);
	}

	r = read(ef->ef_fd, dest, len);
	if (r != -1 && (size_t)r == len)
		return (0);
	else
		return (EIO);
}