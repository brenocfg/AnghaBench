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
struct file_offset_struct {int file_offset; } ;

/* Variables and functions */

__attribute__((used)) static int
offset_cmp(struct file_offset_struct *f1, struct file_offset_struct *f2)
{
	return (f1->file_offset - f2->file_offset);
}