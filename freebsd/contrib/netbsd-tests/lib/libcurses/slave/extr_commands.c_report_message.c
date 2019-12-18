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

/* Variables and functions */
 size_t WRITE_PIPE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * slvpipe ; 
 int strlen (char const*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
report_message(int type, const char *status)
{
	int len;

	len = strlen(status);

	if (write(slvpipe[WRITE_PIPE], &type, sizeof(int)) < 0)
		err(1, "command pipe write for message type failed");

	if (write(slvpipe[WRITE_PIPE], &len, sizeof(int)) < 0)
		err(1, "command pipe write for message length failed");

	if (write(slvpipe[WRITE_PIPE], status, len) < 0)
		err(1, "command pipe write of message data failed");
}