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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sq_must_quote (char const) ; 

__attribute__((used)) static size_t next_quote_pos(const char *s, ssize_t maxlen)
{
	size_t len;
	if (maxlen < 0) {
		for (len = 0; !sq_must_quote(s[len]); len++);
	} else {
		for (len = 0; len < maxlen && !sq_must_quote(s[len]); len++);
	}
	return len;
}