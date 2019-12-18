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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const,char const) ; 

__attribute__((used)) static int 
hexa2int4(const char *a)
{
	if ('0' <= *a && *a <= '9')
		return (*a - '0');

	if ('A' <= *a && *a <= 'F')
		return (*a - 'A' + 0xa);

	if ('a' <= *a && *a <= 'f')
		return (*a - 'a' + 0xa);

	syslog(LOG_ERR, "Invalid hex character: '%c' (%#x)", *a, *a);
	exit(255);
}