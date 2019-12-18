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
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,char*) ; 
 scalar_t__ rump_sys_read (int,char*,int) ; 
 int /*<<< orphan*/  rump_sys_write (int,char const*,scalar_t__) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
sendsome(int from, int to)
{
	size_t i;
	ssize_t cnt;
	static const char msg[] = "hello world\n";
	char buf[sizeof(msg)+10];

	memset(buf, 0, sizeof(buf));
	rump_sys_write(from, msg, strlen(msg));
	cnt = rump_sys_read(to, buf, sizeof(buf));
	if (cnt < (ssize_t)strlen(msg)) {
		printf("short message read: %zd chars: \"%s\"\n", cnt, buf);
		return 1;
	}
	for (i = 0; i < sizeof(buf); i++) {
		if (buf[i] == '\r' || buf[i] == '\n') {
			buf[i] = '\n';
			buf[i+1] = '\0';
			break;
		}
	}

	return strcmp(buf, msg) != 0;
}