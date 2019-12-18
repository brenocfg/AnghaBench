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
 int MSG_DONTWAIT ; 
 int MSG_WAITALL ; 
 int flags ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char const*,int) ; 
 int use_async ; 
 int use_fork ; 
 int use_rgai ; 
 scalar_t__ use_rs ; 
 int verify ; 

__attribute__((used)) static int set_test_opt(const char *arg)
{
	if (strlen(arg) == 1) {
		switch (arg[0]) {
		case 's':
			use_rs = 0;
			break;
		case 'a':
			use_async = 1;
			break;
		case 'b':
			flags = (flags & ~MSG_DONTWAIT) | MSG_WAITALL;
			break;
		case 'f':
			use_fork = 1;
			use_rs = 0;
			break;
		case 'n':
			flags |= MSG_DONTWAIT;
			break;
		case 'r':
			use_rgai = 1;
			break;
		case 'v':
			verify = 1;
			break;
		default:
			return -1;
		}
	} else {
		if (!strncasecmp("socket", arg, 6)) {
			use_rs = 0;
		} else if (!strncasecmp("async", arg, 5)) {
			use_async = 1;
		} else if (!strncasecmp("block", arg, 5)) {
			flags = (flags & ~MSG_DONTWAIT) | MSG_WAITALL;
		} else if (!strncasecmp("nonblock", arg, 8)) {
			flags |= MSG_DONTWAIT;
		} else if (!strncasecmp("resolve", arg, 7)) {
			use_rgai = 1;
		} else if (!strncasecmp("verify", arg, 6)) {
			verify = 1;
		} else if (!strncasecmp("fork", arg, 4)) {
			use_fork = 1;
			use_rs = 0;
		} else {
			return -1;
		}
	}
	return 0;
}