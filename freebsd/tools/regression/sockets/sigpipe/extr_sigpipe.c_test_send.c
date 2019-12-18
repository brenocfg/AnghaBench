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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 scalar_t__ EPIPE ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*,scalar_t__) ; 
 scalar_t__ send (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_send(const char *testname, int sock)
{
	ssize_t len;
	char ch;

	ch = 0;
	len = send(sock, &ch, sizeof(ch), 0);
	if (len < 0) {
		if (errno == EPIPE)
			return;
		err(-1, "%s: send", testname);
	}
	errx(-1, "%s: send: returned %zd", testname, len);
}