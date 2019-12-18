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
typedef  char u8 ;

/* Variables and functions */
 char* dup_binstr (char const*,size_t) ; 

char * sim_get_username(const u8 *identity, size_t identity_len)
{
	size_t pos;

	if (identity == NULL)
		return NULL;

	for (pos = 0; pos < identity_len; pos++) {
		if (identity[pos] == '@' || identity[pos] == '\0')
			break;
	}

	return dup_binstr(identity, pos);
}