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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  send_sideband (int,int,char*,int,scalar_t__) ; 
 scalar_t__ use_sideband ; 
 scalar_t__ vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int xsnprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  xwrite (int,char*,int) ; 

__attribute__((used)) static void report_message(const char *prefix, const char *err, va_list params)
{
	int sz;
	char msg[4096];

	sz = xsnprintf(msg, sizeof(msg), "%s", prefix);
	sz += vsnprintf(msg + sz, sizeof(msg) - sz, err, params);
	if (sz > (sizeof(msg) - 1))
		sz = sizeof(msg) - 1;
	msg[sz++] = '\n';

	if (use_sideband)
		send_sideband(1, 2, msg, sz, use_sideband);
	else
		xwrite(2, msg, sz);
}