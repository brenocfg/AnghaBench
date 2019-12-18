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
 int bid_keycmp (char const*,char*,scalar_t__) ; 
 int bid_keyword (char const*,scalar_t__) ; 

__attribute__((used)) static int
bid_keyword_list(const char *p,  ssize_t len, int unset, int last_is_path)
{
	int l;
	int keycnt = 0;

	while (len > 0 && *p) {
		int blank = 0;

		/* Test whether there are blank characters in the line. */
		while (len >0 && (*p == ' ' || *p == '\t')) {
			++p;
			--len;
			blank = 1;
		}
		if (*p == '\n' || *p == '\r')
			break;
		if (p[0] == '\\' && (p[1] == '\n' || p[1] == '\r'))
			break;
		if (!blank && !last_is_path) /* No blank character. */
			return (-1);
		if (last_is_path && len == 0)
				return (keycnt);

		if (unset) {
			l = bid_keycmp(p, "all", len);
			if (l > 0)
				return (1);
		}
		/* Test whether there is a correct key in the line. */
		l = bid_keyword(p, len);
		if (l == 0)
			return (-1);/* Unknown keyword was found. */
		p += l;
		len -= l;
		keycnt++;

		/* Skip value */
		if (*p == '=') {
			int value = 0;
			++p;
			--len;
			while (len > 0 && *p != ' ' && *p != '\t') {
				++p;
				--len;
				value = 1;
			}
			/* A keyword should have a its value unless
			 * "/unset" operation. */ 
			if (!unset && value == 0)
				return (-1);
		}
	}
	return (keycnt);
}