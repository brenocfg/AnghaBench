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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ radix_strlen_t ;

/* Variables and functions */

__attribute__((used)) static radix_strlen_t
ldns_radix_str_common(uint8_t* str1, radix_strlen_t len1,
	uint8_t* str2, radix_strlen_t len2)
{
	radix_strlen_t i, max = (len1<len2)?len1:len2;
	for (i=0; i<max; i++) {
		if (str1[i] != str2[i]) {
			return i;
		}
	}
	return max;
}