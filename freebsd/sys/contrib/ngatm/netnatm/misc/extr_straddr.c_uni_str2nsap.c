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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  isascii (int) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ islower (int) ; 
 int /*<<< orphan*/  isxdigit (int) ; 

int
uni_str2nsap(u_char *out, const char *in)
{
	int i;
	int c;

	for(i = 0; i < 20; i++) {
		while((c = *in++) == '.')
			;
		if(!isascii(c) || !isxdigit(c))
			return -1;
		out[i] = isdigit(c) ? (c - '0')
			: islower(c) ? (c - 'a' + 10)
			: (c - 'A' + 10);
		out[i] <<= 4;
		c = *in++;
		if(!isascii(c) || !isxdigit(c))
			return -1;
		out[i] |= isdigit(c) ? (c - '0')
			: islower(c) ? (c - 'a' + 10)
			: (c - 'A' + 10);
	}
	return *in != '\0';
}