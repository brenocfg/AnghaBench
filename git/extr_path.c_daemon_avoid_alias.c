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

int daemon_avoid_alias(const char *p)
{
	int sl, ndot;

	/*
	 * This resurrects the belts and suspenders paranoia check by HPA
	 * done in <435560F7.4080006@zytor.com> thread, now enter_repo()
	 * does not do getcwd() based path canonicalization.
	 *
	 * sl becomes true immediately after seeing '/' and continues to
	 * be true as long as dots continue after that without intervening
	 * non-dot character.
	 */
	if (!p || (*p != '/' && *p != '~'))
		return -1;
	sl = 1; ndot = 0;
	p++;

	while (1) {
		char ch = *p++;
		if (sl) {
			if (ch == '.')
				ndot++;
			else if (ch == '/') {
				if (ndot < 3)
					/* reject //, /./ and /../ */
					return -1;
				ndot = 0;
			}
			else if (ch == 0) {
				if (0 < ndot && ndot < 3)
					/* reject /.$ and /..$ */
					return -1;
				return 0;
			}
			else
				sl = ndot = 0;
		}
		else if (ch == 0)
			return 0;
		else if (ch == '/') {
			sl = 1;
			ndot = 0;
		}
	}
}