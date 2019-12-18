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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ a ;

/* Variables and functions */
 int /*<<< orphan*/  evutil_snprintf (char*,int,char*,int,int,int,int) ; 
 int ntohl (int) ; 

__attribute__((used)) static const char *
debug_ntoa(u32 address)
{
	static char buf[32];
	u32 a = ntohl(address);
	evutil_snprintf(buf, sizeof(buf), "%d.%d.%d.%d",
					(int)(u8)((a>>24)&0xff),
					(int)(u8)((a>>16)&0xff),
					(int)(u8)((a>>8 )&0xff),
					(int)(u8)((a	)&0xff));
	return buf;
}