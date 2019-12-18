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
typedef  scalar_t__ radix_strlen_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
ldns_radix_str_is_prefix(uint8_t* str1, radix_strlen_t len1,
	uint8_t* str2, radix_strlen_t len2)
{
	if (len1 == 0) {
		return 1; /* empty prefix is also a prefix */
	}
	if (len1 > len2) {
		return 0; /* len1 is longer so str1 cannot be a prefix */
	}
	return (memcmp(str1, str2, len1) == 0);
}