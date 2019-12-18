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
struct vdso_timekeep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_TIMEKEEP ; 
 int _elf_aux_info (int /*<<< orphan*/ ,struct vdso_timekeep**,int) ; 

int
__vdso_gettimekeep(struct vdso_timekeep **tk)
{

	return (_elf_aux_info(AT_TIMEKEEP, tk, sizeof(*tk)));
}