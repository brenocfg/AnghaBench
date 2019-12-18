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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ IS_SURROGATE_PAIR_LA (int /*<<< orphan*/ ) ; 
 int _utf8_to_unicode (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int
utf8_to_unicode(uint32_t *pwc, const char *s, size_t n)
{
	int cnt;

	cnt = _utf8_to_unicode(pwc, s, n);
	/* Any of Surrogate pair is not legal Unicode values. */
	if (cnt == 3 && IS_SURROGATE_PAIR_LA(*pwc))
		return (-3);
	return (cnt);
}