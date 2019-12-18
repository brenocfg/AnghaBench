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
typedef  int saint_t ;

/* Variables and functions */
 int SAIS_CORE (unsigned char const*,int*,int /*<<< orphan*/ ,int,int,int) ; 

int SAIS_MAIN(const unsigned char *T, saint_t *SA, saint_t n, int k)
{
	if (T == NULL || SA == NULL || T[n - 1] != '\0' || n <= 0) return -1;
	if (k < 0 || k > 256) k = 256;
	return SAIS_CORE(T, SA, 0, n, (saint_t)k, 1);
}