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

const u8 * mschapv2_remove_domain(const u8 *username, size_t *len)
{
	size_t i;

	/*
	 * MSCHAPv2 does not include optional domain name in the
	 * challenge-response calculation, so remove domain prefix
	 * (if present).
	 */

	for (i = 0; i < *len; i++) {
		if (username[i] == '\\') {
			*len -= i + 1;
			return username + i + 1;
		}
	}

	return username;
}