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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_puts (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int extract_path(git_buf *buf, const char *spec, size_t *pos)
{
	git_buf_clear(buf);

	assert(spec[*pos] == ':');

	(*pos)++;

	if (git_buf_puts(buf, spec + *pos) < 0)
		return -1;

	*pos += git_buf_len(buf);

	return 0;
}