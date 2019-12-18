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
typedef  scalar_t__ isc_boolean_t ;

/* Variables and functions */
 int tolower (unsigned char) ; 

__attribute__((used)) static inline unsigned int
hash(const char *key, isc_boolean_t case_sensitive) {
	const char *s;
	unsigned int h = 0;
	int c;

	/*
	 * This hash function is similar to the one Ousterhout
	 * uses in Tcl.
	 */

	if (case_sensitive) {
		for (s = key; *s != '\0'; s++) {
			h += (h << 3) + *s;
		}
	} else {
		for (s = key; *s != '\0'; s++) {
			c = *s;
			c = tolower((unsigned char)c);
			h += (h << 3) + c;
		}
	}

	return (h);
}