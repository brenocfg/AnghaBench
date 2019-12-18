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
typedef  int uint32_t ;

/* Variables and functions */
 int ffs (int) ; 

__attribute__((used)) static inline int
e82545_size_stat_index(uint32_t size)
{
	if (size <= 64) {
		return 0;
	} else if (size >= 1024) {
		return 5;
	} else {
		/* should be 1-4 */
		return (ffs(size) - 6);
	}
}