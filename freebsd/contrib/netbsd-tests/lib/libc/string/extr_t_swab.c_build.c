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
 size_t MAXCHK ; 

__attribute__((used)) static void
build(char *a, char *b, size_t n) {
	size_t i;

	n >>= 1;
	for (i = 0; i < n; i += 2) {
		b[i+1] = a[i] = (char)i;
		b[i] = a[i+1] = (char)(i+1);
	}
	for (n <<= 1; n < MAXCHK; n++)
		a[n] = b[n] = (char)~0;
}