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
typedef  int /*<<< orphan*/  ctf_sect_t ;

/* Variables and functions */
 void const* MAP_FAILED ; 

const void *
ctf_sect_mmap(ctf_sect_t *sp, int fd)
{
	return (MAP_FAILED); /* we don't support this in the kernel */
}