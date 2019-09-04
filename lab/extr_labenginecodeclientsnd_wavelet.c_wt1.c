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
 int /*<<< orphan*/  daub4 (float*,unsigned long,int) ; 

void wt1(float a[], unsigned long n, int isign)
{
	unsigned long nn;
	int inverseStartLength = n/4;
	if (n < inverseStartLength) return;
	if (isign >= 0) {
		for (nn=n;nn>=inverseStartLength;nn>>=1) daub4(a,nn,isign);
	} else {
		for (nn=inverseStartLength;nn<=n;nn<<=1) daub4(a,nn,isign);
	}
}