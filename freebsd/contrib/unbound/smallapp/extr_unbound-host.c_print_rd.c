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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  sldns_wire2str_rdata_buf (int /*<<< orphan*/ *,size_t,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_rd(int t, char* data, size_t len)
{
	char s[65535];
	sldns_wire2str_rdata_buf((uint8_t*)data, len, s, sizeof(s), (uint16_t)t);
	printf(" %s", s);
}