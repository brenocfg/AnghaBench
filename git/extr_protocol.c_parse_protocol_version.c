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
typedef  enum protocol_version { ____Placeholder_protocol_version } protocol_version ;

/* Variables and functions */
 int protocol_unknown_version ; 
 int protocol_v0 ; 
 int protocol_v1 ; 
 int protocol_v2 ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum protocol_version parse_protocol_version(const char *value)
{
	if (!strcmp(value, "0"))
		return protocol_v0;
	else if (!strcmp(value, "1"))
		return protocol_v1;
	else if (!strcmp(value, "2"))
		return protocol_v2;
	else
		return protocol_unknown_version;
}