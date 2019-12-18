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
 int /*<<< orphan*/  __ksplit_aux ; 
 scalar_t__ isgraph (int) ; 
 scalar_t__ isspace (int) ; 
 int strlen (char*) ; 

int ksplit_core(char *s, int delimiter, int *_max, int **_offsets)
{
	int i, n, max, last_char, last_start, *offsets, l;
	n = 0; max = *_max; offsets = *_offsets;
	l = strlen(s);
	
#define __ksplit_aux do {						\
		if (_offsets) {						\
			s[i] = 0;					\
			if (n == max) {					\
				int *tmp;				\
				max = max? max<<1 : 2;			\
				if ((tmp = (int*)realloc(offsets, sizeof(int) * max))) {  \
					offsets = tmp;			\
				} else	{				\
					free(offsets);			\
					*_offsets = NULL;		\
					return 0;			\
				}					\
			}						\
			offsets[n++] = last_start;			\
		} else ++n;						\
	} while (0)

	for (i = 0, last_char = last_start = 0; i <= l; ++i) {
		if (delimiter == 0) {
			if (isspace(s[i]) || s[i] == 0) {
				if (isgraph(last_char)) __ksplit_aux; // the end of a field
			} else {
				if (isspace(last_char) || last_char == 0) last_start = i;
			}
		} else {
			if (s[i] == delimiter || s[i] == 0) {
				if (last_char != 0 && last_char != delimiter) __ksplit_aux; // the end of a field
			} else {
				if (last_char == delimiter || last_char == 0) last_start = i;
			}
		}
		last_char = s[i];
	}
	*_max = max; *_offsets = offsets;
	return n;
}