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

/* Variables and functions */

__attribute__((used)) static int
bt_hex_nibble(char nibble)
{
	if ('0' <= nibble && nibble <= '9')
		return (nibble - '0');

	if ('a' <= nibble && nibble <= 'f')
		return (nibble - 'a' + 0xa);

	if ('A' <= nibble && nibble <= 'F')
		return (nibble - 'A' + 0xa);

	return (-1);
}