#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {scalar_t__ (* arch_readin ) (int,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_1__ archsw ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ stub1 (int,int /*<<< orphan*/ ,size_t) ; 

int
kern_pread(int fd, vm_offset_t dest, size_t len, off_t off)
{

	if (lseek(fd, off, SEEK_SET) == -1) {
#ifdef DEBUG
		printf("\nlseek failed\n");
#endif
		return (-1);
	}
	if ((size_t)archsw.arch_readin(fd, dest, len) != len) {
#ifdef DEBUG
		printf("\nreadin failed\n");
#endif
		return (-1);
	}
	return (0);
}