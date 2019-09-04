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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 char* git__calloc (int,int) ; 
 char* git_buf_detach (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_init (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_putc (int /*<<< orphan*/ *,char const) ; 
 char const* git_config_escaped ; 
 char const* git_config_escapes ; 
 char* strchr (char const*,char const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *escape_value(const char *ptr)
{
	git_buf buf;
	size_t len;
	const char *esc;

	assert(ptr);

	len = strlen(ptr);
	if (!len)
		return git__calloc(1, sizeof(char));

	if (git_buf_init(&buf, len) < 0)
		return NULL;

	while (*ptr != '\0') {
		if ((esc = strchr(git_config_escaped, *ptr)) != NULL) {
			git_buf_putc(&buf, '\\');
			git_buf_putc(&buf, git_config_escapes[esc - git_config_escaped]);
		} else {
			git_buf_putc(&buf, *ptr);
		}
		ptr++;
	}

	if (git_buf_oom(&buf))
		return NULL;

	return git_buf_detach(&buf);
}