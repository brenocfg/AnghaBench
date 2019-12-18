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
 int ARRAY_SIZE (char**) ; 
 char* ENUM2STR (int /*<<< orphan*/ ) ; 
#define  SDP_MID_ABORT 139 
#define  SDP_MID_CHRCVBUF 138 
#define  SDP_MID_CHRCVBUF_ACK 137 
#define  SDP_MID_DATA 136 
#define  SDP_MID_DISCONN 135 
#define  SDP_MID_HELLO 134 
#define  SDP_MID_HELLO_ACK 133 
#define  SDP_MID_RDMARDCOMPL 132 
#define  SDP_MID_SENDSM 131 
#define  SDP_MID_SINKAVAIL 130 
#define  SDP_MID_SRCAVAIL 129 
#define  SDP_MID_SRCAVAIL_CANCEL 128 

__attribute__((used)) static inline char *mid2str(int mid)
{
#define ENUM2STR(e) [e] = #e
	static char *mid2str[] = {
		ENUM2STR(SDP_MID_HELLO),
		ENUM2STR(SDP_MID_HELLO_ACK),
		ENUM2STR(SDP_MID_ABORT),
		ENUM2STR(SDP_MID_DISCONN),
		ENUM2STR(SDP_MID_SENDSM),
		ENUM2STR(SDP_MID_RDMARDCOMPL),
		ENUM2STR(SDP_MID_SRCAVAIL_CANCEL),
		ENUM2STR(SDP_MID_CHRCVBUF),
		ENUM2STR(SDP_MID_CHRCVBUF_ACK),
		ENUM2STR(SDP_MID_DATA),
		ENUM2STR(SDP_MID_SRCAVAIL),
		ENUM2STR(SDP_MID_SINKAVAIL),
	};

	if (mid >= ARRAY_SIZE(mid2str))
		return NULL;

	return mid2str[mid];
}