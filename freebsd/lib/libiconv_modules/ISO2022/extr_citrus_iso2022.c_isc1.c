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
typedef  int __uint8_t ;

/* Variables and functions */

__attribute__((used)) static __inline bool isc1(__uint8_t x)
{

	return (0x80 <= x && x <= 0x9f);
}