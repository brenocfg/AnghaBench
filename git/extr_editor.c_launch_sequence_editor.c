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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_sequence_editor () ; 
 int launch_specified_editor (int /*<<< orphan*/ ,char const*,struct strbuf*,char const* const*) ; 

int launch_sequence_editor(const char *path, struct strbuf *buffer,
			   const char *const *env)
{
	return launch_specified_editor(git_sequence_editor(), path, buffer, env);
}