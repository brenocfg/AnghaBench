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
typedef  int uint8_t ;

/* Variables and functions */
 scalar_t__ memcmp (int const*,int const*,int) ; 

__attribute__((used)) static __inline int
match_id(const uint8_t *ie, const uint8_t *val, int len)
{
	return (ie[1] == len && memcmp(ie+2, val, len) == 0);
}