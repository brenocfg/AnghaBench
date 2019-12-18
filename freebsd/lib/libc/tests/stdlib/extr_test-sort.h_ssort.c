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

__attribute__((used)) static void
ssort(int v[], int nmemb)
{
	int i, j, k;

	for (i = 0; i < nmemb; i++) {
		for (j = i + 1; j < nmemb; j++) {
			if (v[j] < v[i]) {
				k = v[i];
				v[i] = v[j];
				v[j] = k;
			}
		}
	}
}