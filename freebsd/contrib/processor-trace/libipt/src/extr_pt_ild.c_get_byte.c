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
typedef  size_t uint8_t ;
struct pt_ild {size_t* itext; } ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t get_byte(const struct pt_ild *ild, uint8_t i)
{
	return ild->itext[i];
}