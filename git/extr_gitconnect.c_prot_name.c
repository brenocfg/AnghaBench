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
typedef  enum protocol { ____Placeholder_protocol } protocol ;

/* Variables and functions */
#define  PROTO_FILE 131 
#define  PROTO_GIT 130 
#define  PROTO_LOCAL 129 
#define  PROTO_SSH 128 

__attribute__((used)) static const char *prot_name(enum protocol protocol)
{
	switch (protocol) {
		case PROTO_LOCAL:
		case PROTO_FILE:
			return "file";
		case PROTO_SSH:
			return "ssh";
		case PROTO_GIT:
			return "git";
		default:
			return "unknown protocol";
	}
}