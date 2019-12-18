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
 int /*<<< orphan*/  AT91_ST_CRTR ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_st ; 

__attribute__((used)) static inline unsigned long read_CRTR(void)
{
	unsigned int x1, x2;

	regmap_read(regmap_st, AT91_ST_CRTR, &x1);
	do {
		regmap_read(regmap_st, AT91_ST_CRTR, &x2);
		if (x1 == x2)
			break;
		x1 = x2;
	} while (1);
	return x1;
}