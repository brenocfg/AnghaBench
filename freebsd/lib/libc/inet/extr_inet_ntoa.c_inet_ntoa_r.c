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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,struct in_addr*,char*,int /*<<< orphan*/ ) ; 

char *
inet_ntoa_r(struct in_addr in, char *buf, socklen_t size)
{

	(void) inet_ntop(AF_INET, &in, buf, size);
	return (buf);
}