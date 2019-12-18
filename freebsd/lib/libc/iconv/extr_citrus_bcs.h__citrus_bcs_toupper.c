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

/* Variables and functions */
 scalar_t__ _citrus_bcs_islower (char) ; 

__attribute__((used)) static __inline uint8_t
_citrus_bcs_toupper(uint8_t c)
{

	return (_citrus_bcs_islower(c) ? (c - 'a' + 'A') : c);
}