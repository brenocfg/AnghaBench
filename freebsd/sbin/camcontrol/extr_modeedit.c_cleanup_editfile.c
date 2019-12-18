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
 int /*<<< orphan*/ * edit_file ; 
 int /*<<< orphan*/  edit_path ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cleanup_editfile(void)
{
	if (edit_file == NULL)
		return;
	if (fclose(edit_file) != 0 || unlink(edit_path) != 0)
		warn("%s", edit_path);
	edit_file = NULL;
}