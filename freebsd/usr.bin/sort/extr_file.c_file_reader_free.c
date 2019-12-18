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
struct file_reader {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_reader_clean (struct file_reader*) ; 
 int /*<<< orphan*/  sort_free (struct file_reader*) ; 

void
file_reader_free(struct file_reader *fr)
{

	if (fr) {
		file_reader_clean(fr);
		sort_free(fr);
	}
}