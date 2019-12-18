#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int errno ; 
 int /*<<< orphan*/  fail (char const*,char*) ; 
 int /*<<< orphan*/  failx (char const*,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ipdivert_bind(const char *test, int s, u_short port, int expect)
{
	struct sockaddr_in sin;
	int err;

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);

	err = bind(s, (struct sockaddr *)&sin, sizeof(sin));
	if (err < 0) {
		if (expect == 0)
			fail(test, "bind");
		if (errno != expect)
			fail(test, "bind");
	} else {
		if (expect != 0)
			failx(test, "bind");
	}
}