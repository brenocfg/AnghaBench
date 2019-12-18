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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
hash_str(const char *str)
{
	const uint8_t *s = (const uint8_t *)str;
	uint8_t c;
	uint32_t hash = 0;
	while ((c = *s++) != '\0') 
		hash = hash * 33 + c;           /* "perl": k=33, r=r+r/32 */
	return hash + (hash >> 5);
}