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
typedef  int /*<<< orphan*/  bitstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bit_clear (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
bit_change(bitstr_t *bitstr, int bit, int value)
{
	if (value)
		bit_set(bitstr, bit);
	else
		bit_clear(bitstr, bit);
}