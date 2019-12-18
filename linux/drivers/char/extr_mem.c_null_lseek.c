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
struct file {scalar_t__ f_pos; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */

__attribute__((used)) static loff_t null_lseek(struct file *file, loff_t offset, int orig)
{
	return file->f_pos = 0;
}