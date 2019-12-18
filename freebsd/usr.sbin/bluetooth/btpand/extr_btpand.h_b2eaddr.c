#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * b; } ;
typedef  TYPE_1__ bdaddr_t ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 

__attribute__((used)) static inline void
b2eaddr(void *dst, bdaddr_t *src)
{
	uint8_t *d = dst;
	int i;

	for (i = 0; i < ETHER_ADDR_LEN; i++)
		d[i] = src->b[ETHER_ADDR_LEN - i - 1];
}