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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int ns_name_compress (char const*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 

int
dn_comp(const char *src, u_char *dst, int dstsiz,
	u_char **dnptrs, u_char **lastdnptr)
{
	return (ns_name_compress(src, dst, (size_t)dstsiz,
				 (const u_char **)dnptrs,
				 (const u_char **)lastdnptr));
}