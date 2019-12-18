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
struct loop_device {int /*<<< orphan*/  lo_sizelimit; int /*<<< orphan*/  lo_offset; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 

__attribute__((used)) static loff_t get_loop_size(struct loop_device *lo, struct file *file)
{
	return get_size(lo->lo_offset, lo->lo_sizelimit, file);
}