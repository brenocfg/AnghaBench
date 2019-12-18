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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  message_error (int /*<<< orphan*/ ) ; 

extern bool
is_empty_filename(const char *filename)
{
	if (filename[0] == '\0') {
		message_error(_("Empty filename, skipping"));
		return true;
	}

	return false;
}