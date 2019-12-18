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
 scalar_t__ tolower (unsigned char const) ; 

__attribute__((used)) static int
name_eq(const unsigned char *a, const unsigned char *b) {
	const unsigned char *a_save = a;
	for (;;) {
		int i;
		int lena = *a++;
		int lenb = *b++;
		if (lena != lenb)
			return 0;
		if (lena == 0)
			return a - a_save;
		for (i = 0; i < lena; i++)
			if (tolower(a[i]) != tolower(b[i]))
				return 0;
		a += lena;
		b += lena;
	}
}