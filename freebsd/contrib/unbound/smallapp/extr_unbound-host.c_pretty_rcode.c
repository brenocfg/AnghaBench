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
typedef  int /*<<< orphan*/  d ;

/* Variables and functions */
 int /*<<< orphan*/  sldns_wire2str_rcode_buf (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static void
pretty_rcode(char* s, size_t len, int r)
{
	char d[16];
	sldns_wire2str_rcode_buf(r, d, sizeof(d));
	snprintf(s, len, "%s", d);
}