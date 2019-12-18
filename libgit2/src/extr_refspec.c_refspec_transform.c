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
 int /*<<< orphan*/  git_buf_put (int /*<<< orphan*/ *,char const*,size_t) ; 
 int git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int refspec_transform(
	git_buf *out, const char *from, const char *to, const char *name)
{
	const char *from_star, *to_star;
	size_t replacement_len, star_offset;

	git_buf_sanitize(out);
	git_buf_clear(out);

	/*
	 * There are two parts to each side of a refspec, the bit
	 * before the star and the bit after it. The star can be in
	 * the middle of the pattern, so we need to look at each bit
	 * individually.
	 */
	from_star = strchr(from, '*');
	to_star = strchr(to, '*');

	assert(from_star && to_star);

	/* star offset, both in 'from' and in 'name' */
	star_offset = from_star - from;

	/* the first half is copied over */
	git_buf_put(out, to, to_star - to);

	/*
	 * Copy over the name, but exclude the trailing part in "from" starting
	 * after the glob
	 */
	replacement_len = strlen(name + star_offset) - strlen(from_star + 1);
	git_buf_put(out, name + star_offset, replacement_len);

	return git_buf_puts(out, to_star + 1);
}