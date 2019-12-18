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
struct iaddr {int len; int /*<<< orphan*/  iabuf; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DOT ; 
 scalar_t__ parse_numeric_aggregate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int,int) ; 

int
parse_ip_addr(FILE *cfile, struct iaddr *addr)
{
	addr->len = 4;
	if (parse_numeric_aggregate(cfile, addr->iabuf,
	    &addr->len, DOT, 10, 8))
		return (1);
	return (0);
}