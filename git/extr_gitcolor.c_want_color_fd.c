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
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BUG (char*,int) ; 
 int GIT_COLOR_AUTO ; 
 int check_auto_color (int) ; 
 int git_use_color_default ; 

int want_color_fd(int fd, int var)
{
	/*
	 * NEEDSWORK: This function is sometimes used from multiple threads, and
	 * we end up using want_auto racily. That "should not matter" since
	 * we always write the same value, but it's still wrong. This function
	 * is listed in .tsan-suppressions for the time being.
	 */

	static int want_auto[3] = { -1, -1, -1 };

	if (fd < 1 || fd >= ARRAY_SIZE(want_auto))
		BUG("file descriptor out of range: %d", fd);

	if (var < 0)
		var = git_use_color_default;

	if (var == GIT_COLOR_AUTO) {
		if (want_auto[fd] < 0)
			want_auto[fd] = check_auto_color(fd);
		return want_auto[fd];
	}
	return var;
}