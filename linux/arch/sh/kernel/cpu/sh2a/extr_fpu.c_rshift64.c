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

__attribute__((used)) static inline long long rshift64(unsigned long long mh,
		unsigned long long ml, int n)
{
	if (n >= 64)
		return mh >> (n - 64);
	return (mh << (64 - n)) | (ml >> n);
}