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
 int /*<<< orphan*/  rmtape ; 
 int /*<<< orphan*/  rmtconnaborted (int /*<<< orphan*/ ) ; 
 int rmtreply (char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,char const*,scalar_t__) ; 

__attribute__((used)) static int
rmtcall(const char *cmd, const char *buf)
{

	if (write(rmtape, buf, strlen(buf)) != strlen(buf))
		rmtconnaborted(0);
	return (rmtreply(cmd));
}