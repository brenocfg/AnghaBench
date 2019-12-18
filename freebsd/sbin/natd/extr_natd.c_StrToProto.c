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
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int
StrToProto (const char* str)
{
	if (!strcmp (str, "tcp"))
		return IPPROTO_TCP;

	if (!strcmp (str, "udp"))
		return IPPROTO_UDP;

	errx (1, "unknown protocol %s. Expected tcp or udp", str);
}