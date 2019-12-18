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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MODE_EXTRACT ; 
 int file_mode ; 
 int /*<<< orphan*/  msg (char*) ; 
 int /*<<< orphan*/ * open_file (char const*,int) ; 

__attribute__((used)) static int
set_file(FILE **file, const char *name, int mode)
{
	if (file_mode < 0)
		file_mode = mode;
	else if (file_mode != mode) {
		msg("Error: mixing appending and extracting data is not supported\n");
		return 1;
	}

	if (*file) {
		msg("Error: the same append/extract option cannot be used multiple times\n");
		return 1;
	}

	*file = open_file(name, mode == MODE_EXTRACT);
	return !*file;
}