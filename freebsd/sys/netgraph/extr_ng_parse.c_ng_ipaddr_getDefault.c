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
struct ng_parse_type {int dummy; } ;
struct in_addr {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ip ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  bcopy (struct in_addr*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ng_ipaddr_getDefault(const struct ng_parse_type *type,
	const u_char *const start, u_char *buf, int *buflen)
{
	struct in_addr ip = { 0 };

	if (*buflen < sizeof(ip))
		return (ERANGE);
	bcopy(&ip, buf, sizeof(ip));
	*buflen = sizeof(ip);
	return (0);
}