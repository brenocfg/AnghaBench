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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTOV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int const,int /*<<< orphan*/ ,size_t const) ; 

ssize_t
i386_readin(const int fd, vm_offset_t dest, const size_t len)
{
    return (read(fd, PTOV(dest), len));
}