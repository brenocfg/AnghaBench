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
 int /*<<< orphan*/  NS_INADDRSZ ; 
 int /*<<< orphan*/  memmove (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 

void
_map_v4v6_address(const char *src, char *dst)
{
	/* Our caller may update in place. */
	memmove(&dst[12], src, NS_INADDRSZ);
	/* Mark this ipv6 addr as a mapped ipv4. */
	memset(&dst[10], 0xff, 2);
	memset(&dst[0], 0, 10);
}