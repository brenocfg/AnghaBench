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
 int sldns_str_print (char**,size_t*,char*) ; 
 int sldns_wire2str_b64_scan_num (int /*<<< orphan*/ **,size_t*,char**,size_t*,size_t) ; 

int sldns_wire2str_b64_scan(uint8_t** d, size_t* dl, char** s, size_t* sl)
{
	if(*dl == 0) {
		return sldns_str_print(s, sl, "0");
	}
	return sldns_wire2str_b64_scan_num(d, dl, s, sl, *dl);
}