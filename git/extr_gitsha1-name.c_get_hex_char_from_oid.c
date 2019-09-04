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
struct object_id {int* hash; } ;

/* Variables and functions */

__attribute__((used)) static inline char get_hex_char_from_oid(const struct object_id *oid,
					 unsigned int pos)
{
	static const char hex[] = "0123456789abcdef";

	if ((pos & 1) == 0)
		return hex[oid->hash[pos >> 1] >> 4];
	else
		return hex[oid->hash[pos >> 1] & 0xf];
}