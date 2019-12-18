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
struct file_info {scalar_t__ file_size; int /*<<< orphan*/ * file_data; int /*<<< orphan*/ * file_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fi_clean(struct file_info* finfo) {
	if (!finfo)
		return;

	if (finfo->file_name) {
		finfo->file_name = NULL;
	}

	if (finfo->file_data) {
		free(finfo->file_data);
		finfo->file_data = NULL;
	}

	finfo->file_size = 0;
}