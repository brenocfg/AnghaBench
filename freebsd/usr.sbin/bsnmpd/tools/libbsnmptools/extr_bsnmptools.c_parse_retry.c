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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 TYPE_1__ snmp_client ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

int32_t
parse_retry(char *opt_arg)
{
	uint32_t v;
	int32_t saved_errno;

	assert(opt_arg != NULL);

	saved_errno = errno;
	errno = 0;

	v = strtoul(opt_arg, NULL, 10);
	if (errno != 0) {
		warn("Error parsing retries count");
		errno = saved_errno;
		return (-1);
	}

	snmp_client.retries = v;
	errno = saved_errno;
	return (2);
}