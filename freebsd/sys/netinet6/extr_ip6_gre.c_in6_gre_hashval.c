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
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int /*<<< orphan*/  fnv_32_buf (struct in6_addr const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
in6_gre_hashval(const struct in6_addr *src, const struct in6_addr *dst)
{
	uint32_t ret;

	ret = fnv_32_buf(src, sizeof(*src), FNV1_32_INIT);
	return (fnv_32_buf(dst, sizeof(*dst), ret));
}