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
struct diff_filespec {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  diff_free_filespec_data (struct diff_filespec*) ; 
 int /*<<< orphan*/  free (struct diff_filespec*) ; 

void free_filespec(struct diff_filespec *spec)
{
	if (!--spec->count) {
		diff_free_filespec_data(spec);
		free(spec);
	}
}