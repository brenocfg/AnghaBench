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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
priv_netinet_raw(int asroot, int injail, struct test *test)
{
	int error, fd;

	fd = socket(PF_INET, SOCK_RAW, 0);
	if (fd < 0)
		error = -1;
	else
		error = 0;
	if (asroot && injail)
		expect("priv_netinet_raw(asroot, injail)", error, -1, EPERM);
	if (asroot && !injail)
		expect("priv_netinet_raw(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_netinet_raw(!asroot, injail)", error, -1,
		    EPERM);
	if (!asroot && !injail)
		expect("priv_netinet_raw(!asroot, !injail)", error,
		    -1, EPERM);
	if (fd >= 0)
		(void)close(fd);
}