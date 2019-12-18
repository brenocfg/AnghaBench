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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  ip ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,struct in_addr*,int) ; 
 int ng_parse_append (char**,int*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_ipaddr_unparse(const struct ng_parse_type *type,
	const u_char *data, int *off, char *cbuf, int cbuflen)
{
	struct in_addr ip;
	int error;

	bcopy(data + *off, &ip, sizeof(ip));
	if ((error = ng_parse_append(&cbuf, &cbuflen, "%d.%d.%d.%d",
	    ((u_char *)&ip)[0], ((u_char *)&ip)[1],
	    ((u_char *)&ip)[2], ((u_char *)&ip)[3])) != 0)
		return (error);
	*off += sizeof(ip);
	return (0);
}