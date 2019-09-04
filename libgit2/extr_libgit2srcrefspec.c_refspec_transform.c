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
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int refspec_transform(
	git_buf *out, const char *from, const char *to, const char *name)
{
	const char *from_star, *to_star;
	const char *name_slash, *from_slash;
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

	/* then we copy over the replacement, from the star's offset to the next slash in 'name' */
	name_slash = strchr(name + star_offset, '/');
	if (!name_slash)
		name_slash = strrchr(name, '\0');

	/* if there is no slash after the star in 'from', we want to copy everything over */
	from_slash = strchr(from + star_offset, '/');
	if (!from_slash)
		name_slash = strrchr(name, '\0');

	replacement_len = (name_slash - name) - star_offset;
	git_buf_put(out, name + star_offset, replacement_len);

	return git_buf_puts(out, to_star + 1);
}