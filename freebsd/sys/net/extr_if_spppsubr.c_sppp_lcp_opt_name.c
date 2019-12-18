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
typedef  int u_char ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  LCP_OPT_ADDR_COMP 134 
#define  LCP_OPT_ASYNC_MAP 133 
#define  LCP_OPT_AUTH_PROTO 132 
#define  LCP_OPT_MAGIC 131 
#define  LCP_OPT_MRU 130 
#define  LCP_OPT_PROTO_COMP 129 
#define  LCP_OPT_QUAL_PROTO 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
sppp_lcp_opt_name(u_char opt)
{
	static char buf[12];
	switch (opt) {
	case LCP_OPT_MRU:		return "mru";
	case LCP_OPT_ASYNC_MAP:		return "async-map";
	case LCP_OPT_AUTH_PROTO:	return "auth-proto";
	case LCP_OPT_QUAL_PROTO:	return "qual-proto";
	case LCP_OPT_MAGIC:		return "magic";
	case LCP_OPT_PROTO_COMP:	return "proto-comp";
	case LCP_OPT_ADDR_COMP:		return "addr-comp";
	}
	snprintf (buf, sizeof(buf), "lcp/0x%x", opt);
	return buf;
}