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
struct archive_read {int /*<<< orphan*/  filter; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 void const* __archive_read_filter_ahead (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

const void *
__archive_read_ahead(struct archive_read *a, size_t min, ssize_t *avail)
{
	return (__archive_read_filter_ahead(a->filter, min, avail));
}