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
 int /*<<< orphan*/  SIGPIPE ; 
 scalar_t__ rmtape ; 
 int /*<<< orphan*/  rmtconnaborted ; 
 int /*<<< orphan*/  rmtgetconn () ; 
 int /*<<< orphan*/ * rmtpeer ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
rmthost(const char *host)
{

	rmtpeer = strdup(host);
	if (rmtpeer == NULL)
		return (0);
	signal(SIGPIPE, rmtconnaborted);
	rmtgetconn();
	if (rmtape < 0)
		return (0);
	return (1);
}