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
typedef  scalar_t__ u_short ;

/* Variables and functions */
#define  PPP_CHAP 129 
#define  PPP_PAP 128 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

const char *
proto_name(u_short proto)
{
	static char buf[12];
	switch (proto) {
	case PPP_PAP:	return "pap";
	case PPP_CHAP:	return "chap";
	}
	sprintf(buf, "0x%x", (unsigned)proto);
	return buf;
}