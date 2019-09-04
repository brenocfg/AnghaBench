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
struct diff_filespec {int /*<<< orphan*/  cnt_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_free_filespec_blob (struct diff_filespec*) ; 

void diff_free_filespec_data(struct diff_filespec *s)
{
	diff_free_filespec_blob(s);
	FREE_AND_NULL(s->cnt_data);
}