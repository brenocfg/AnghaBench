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
struct ip6_rthdr {int /*<<< orphan*/  ip6r_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_RTHDR_TYPE_0 ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  checknum (int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * inet6_rth_init (void*,int,int /*<<< orphan*/ ,int) ; 
 int inet6_rth_segments (void const*) ; 
 int /*<<< orphan*/  set_funcname (char*,int) ; 

void
test_rth_segments()
{
	int	seg;
	char	buf[10240];

	set_funcname("test_rth_segments", sizeof("test_rth_segments\0"));

	/*
	 * Test: invalid routing header type.
	 */
	if (NULL == inet6_rth_init((void *)buf, 10240, IPV6_RTHDR_TYPE_0, 0))
		abort();
	((struct ip6_rthdr *)buf)->ip6r_type = ~IPV6_RTHDR_TYPE_0;
	seg = inet6_rth_segments((const void *)buf);
	checknum(-1, seg, 0, "invalid routing header type\0");

	/*
	 * Test: 0 segments.
	 */
	if (NULL == inet6_rth_init((void *)buf, 10240, IPV6_RTHDR_TYPE_0, 0))
		abort();
	seg = inet6_rth_segments((const void *)buf);
	checknum(0, seg, 0, "0 segments\0");

	/*
	 * Test: 127 segments.
	 */
	if (NULL == inet6_rth_init((void *)buf, 10240, IPV6_RTHDR_TYPE_0, 127))
		abort();
	seg = inet6_rth_segments((const void *)buf);
	checknum(127, seg, 0, "127 segments\0");

	/*
	 * Test: -1 segments.
	 */
/*
	if (NULL == inet6_rth_init((void *)buf, 10240, IPV6_RTHDR_TYPE_0, 0))
		abort();
	((struct ip6_rthdr0 *)buf)->ip6r0_len = -1 * 2;
	seg = inet6_rth_segments((const void *)buf);
	checknum(-1, seg, 0, "-1 segments\0");
*/
	/*
	 * Test: 128 segments.
	 */
/*
	if (NULL == inet6_rth_init((void *)buf, 10240, IPV6_RTHDR_TYPE_0, 127))
		abort();
	((struct ip6_rthdr0 *)buf)->ip6r0_len = 128 * 2;
	seg = inet6_rth_segments((const void *)buf);
	checknum(-1, seg, 0, "128 segments\0");
*/
}