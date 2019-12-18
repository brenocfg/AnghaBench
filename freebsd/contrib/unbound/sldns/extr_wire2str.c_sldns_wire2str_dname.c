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

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  sldns_wire2str_dname_buf (int /*<<< orphan*/ *,size_t,char*,size_t) ; 

char* sldns_wire2str_dname(uint8_t* dname, size_t dname_len)
{
	size_t slen=(size_t)sldns_wire2str_dname_buf(dname, dname_len, NULL, 0);
	char* result = (char*)malloc(slen+1);
	if(!result) return NULL;
	sldns_wire2str_dname_buf(dname, dname_len, result, slen+1);
	return result;
}