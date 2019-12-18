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
 int /*<<< orphan*/  powerof2 (size_t) ; 

__attribute__((used)) static inline size_t
p2roundup(size_t n)
{

	if (!powerof2(n)) {
		n--;
		n |= n >> 1;
		n |= n >> 2;
		n |= n >> 4;
		n |= n >> 8;
		n |= n >> 16;
#if SIZE_T_MAX > 0xffffffffU
		n |= n >> 32;
#endif
		n++;
	}
	return (n);
}