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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */

__attribute__((used)) static int
bid_keycmp(const char *p, const char *key, ssize_t len)
{
	int match_len = 0;

	while (len > 0 && *p && *key) {
		if (*p == *key) {
			--len;
			++p;
			++key;
			++match_len;
			continue;
		}
		return (0);/* Not match */
	}
	if (*key != '\0')
		return (0);/* Not match */

	/* A following character should be specified characters */
	if (p[0] == '=' || p[0] == ' ' || p[0] == '\t' ||
	    p[0] == '\n' || p[0] == '\r' ||
	   (p[0] == '\\' && (p[1] == '\n' || p[1] == '\r')))
		return (match_len);
	return (0);/* Not match */
}