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
struct file {int name_len; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
file_cmp_key(const struct archive_rb_node *n, const void *key)
{
	const struct file *f = (const struct file *)n;

	return (f->name_len - *(const char *)key);
}