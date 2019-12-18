#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_3__ {int tv_sec; } ;
struct TYPE_4__ {TYPE_1__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 TYPE_2__ snmp_client ; 
 int strtol (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

int32_t
parse_timeout(char *opt_arg)
{
	int32_t v, saved_errno;

	assert(opt_arg != NULL);

	saved_errno = errno;
	errno = 0;

	v = strtol(opt_arg, NULL, 10);
	if (errno != 0) {
		warn("Error parsing timeout value");
		errno = saved_errno;
		return (-1);
	}

	snmp_client.timeout.tv_sec = v;
	errno = saved_errno;
	return (2);
}