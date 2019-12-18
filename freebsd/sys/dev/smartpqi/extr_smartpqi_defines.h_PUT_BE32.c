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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PUT_BE16 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void PUT_BE32(uint32_t val, uint8_t *p)
{
        PUT_BE16(val >> 16, p);
        PUT_BE16(val, p + 2);
}