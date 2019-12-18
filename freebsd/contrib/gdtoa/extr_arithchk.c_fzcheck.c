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

__attribute__((used)) static int
fzcheck()
{
	double a, b;
	int i;

	a = 1.;
	b = .1;
	for(i = 155;; b *= b, i >>= 1) {
		if (i & 1) {
			a *= b;
			if (i == 1)
				break;
			}
		}
	b = a * a;
	return b == 0.;
	}