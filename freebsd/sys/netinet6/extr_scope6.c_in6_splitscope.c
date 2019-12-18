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
typedef  int /*<<< orphan*/  uint32_t ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  in6_clearscope (struct in6_addr*) ; 
 int /*<<< orphan*/  in6_getscope (struct in6_addr*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

void
in6_splitscope(const struct in6_addr *src, struct in6_addr *dst,
    uint32_t *scopeid)
{
	uint32_t zoneid;

	*dst = *src;
	zoneid = ntohs(in6_getscope(dst));
	in6_clearscope(dst);
	*scopeid = zoneid;
}