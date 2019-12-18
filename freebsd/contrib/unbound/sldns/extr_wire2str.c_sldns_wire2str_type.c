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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  sldns_wire2str_type_buf (int /*<<< orphan*/ ,char*,int) ; 
 char* strdup (char*) ; 

char* sldns_wire2str_type(uint16_t rrtype)
{
	char buf[16];
	sldns_wire2str_type_buf(rrtype, buf, sizeof(buf));
	return strdup(buf);
}