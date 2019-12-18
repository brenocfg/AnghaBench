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
struct file_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
file_header_swap(struct file_header **fh, size_t i1, size_t i2)
{
	struct file_header *tmp;

	tmp = fh[i1];
	fh[i1] = fh[i2];
	fh[i2] = tmp;
}