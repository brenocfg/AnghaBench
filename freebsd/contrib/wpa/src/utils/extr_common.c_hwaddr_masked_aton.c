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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 char* hwaddr_parse (char const*,scalar_t__*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  os_memset (scalar_t__*,int,int /*<<< orphan*/ ) ; 

int hwaddr_masked_aton(const char *txt, u8 *addr, u8 *mask, u8 maskable)
{
	const char *r;

	/* parse address part */
	r = hwaddr_parse(txt, addr);
	if (!r)
		return -1;

	/* check for optional mask */
	if (*r == '\0' || isspace((unsigned char) *r)) {
		/* no mask specified, assume default */
		os_memset(mask, 0xff, ETH_ALEN);
	} else if (maskable && *r == '/') {
		/* mask specified and allowed */
		r = hwaddr_parse(r + 1, mask);
		/* parser error? */
		if (!r)
			return -1;
	} else {
		/* mask specified but not allowed or trailing garbage */
		return -1;
	}

	return 0;
}