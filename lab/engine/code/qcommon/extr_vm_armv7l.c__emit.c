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
struct TYPE_3__ {scalar_t__ codeLength; scalar_t__ codeBase; } ;
typedef  TYPE_1__ vm_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  memcpy (scalar_t__,unsigned int*,int) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  write (int,unsigned int*,int) ; 

void _emit(vm_t *vm, unsigned isn, int pass)
{
#if 0
	static int fd = -2;
	if (fd == -2)
		fd = open("code.bin", O_TRUNC|O_WRONLY|O_CREAT, 0644);
	if (fd > 0)
		write(fd, &isn, 4);
#endif

	if (pass)
		memcpy(vm->codeBase+vm->codeLength, &isn, 4);
	vm->codeLength+=4;
}