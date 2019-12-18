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
typedef  unsigned int u_int32_t ;

/* Variables and functions */
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
mn_parse_ts(const char *s, int *nbit)
{
	unsigned r;
	int i, j;
	char *p;

	r = 0;
	j = -1;
	*nbit = 0;
	while(*s) {
		i = strtol(s, &p, 0);
		if (i < 0 || i > 31)
			return (0);
		while (j != -1 && j < i) {
			r |= 1 << j++;
			(*nbit)++;
		}
		j = -1;
		r |= 1 << i;
		(*nbit)++;
		if (*p == ',') {
			s = p + 1;
			continue;
		} else if (*p == '-') {
			j = i + 1;
			s = p + 1;
			continue;
		} else if (!*p) {
			break;
		} else {
			return (0);
		}
	}
	return (r);
}