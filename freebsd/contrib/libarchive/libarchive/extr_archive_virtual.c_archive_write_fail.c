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
struct archive {int state; } ;

/* Variables and functions */
 int ARCHIVE_STATE_FATAL ; 

int
archive_write_fail(struct archive *a)
{
	a->state = ARCHIVE_STATE_FATAL;
	return a->state;
}