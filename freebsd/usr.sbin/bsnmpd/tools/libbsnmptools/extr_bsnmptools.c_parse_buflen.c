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
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;
struct TYPE_2__ {scalar_t__ rxbuflen; scalar_t__ txbuflen; } ;

/* Variables and functions */
 scalar_t__ MAX_BUFF_SIZE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 TYPE_1__ snmp_client ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

int32_t
parse_buflen(char *opt_arg)
{
	uint32_t size;
	int32_t saved_errno;

	assert(opt_arg != NULL);

	saved_errno = errno;
	errno = 0;

	size = strtoul(opt_arg, NULL, 10);
	if (errno != 0) {
		warn("Error parsing buffer size");
		errno = saved_errno;
		return (-1);
	}

	if (size > MAX_BUFF_SIZE) {
		warnx("Buffer size too big - %d max allowed", MAX_BUFF_SIZE);
		errno = saved_errno;
		return (-1);
	}

	snmp_client.txbuflen = snmp_client.rxbuflen = size;
	errno = saved_errno;
	return (2);
}