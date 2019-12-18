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
 char tolower (char) ; 

__attribute__((used)) static inline double
ucl_lex_time_multiplier (const unsigned char c) {
	const struct {
		char c;
		double mult;
	} multipliers[] = {
			{'m', 60},
			{'h', 60 * 60},
			{'d', 60 * 60 * 24},
			{'w', 60 * 60 * 24 * 7},
			{'y', 60 * 60 * 24 * 365}
	};
	int i;

	for (i = 0; i < 5; i ++) {
		if (tolower (c) == multipliers[i].c) {
			return multipliers[i].mult;
		}
	}

	return 1;
}