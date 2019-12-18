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
 char* getenv (char*) ; 
 int /*<<< orphan*/  git_config_get_string_const (char*,char const**) ; 
 char* git_editor () ; 

const char *git_sequence_editor(void)
{
	const char *editor = getenv("GIT_SEQUENCE_EDITOR");

	if (!editor)
		git_config_get_string_const("sequence.editor", &editor);
	if (!editor)
		editor = git_editor();

	return editor;
}