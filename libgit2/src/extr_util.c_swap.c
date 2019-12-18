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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static void swap(uint8_t *a, uint8_t *b, size_t elsize)
{
	char tmp[256];

	while (elsize) {
		size_t n = elsize < sizeof(tmp) ? elsize : sizeof(tmp);
		memcpy(tmp, a + elsize - n, n);
		memcpy(a + elsize - n, b + elsize - n, n);
		memcpy(b + elsize - n, tmp, n);
		elsize -= n;
	}
}