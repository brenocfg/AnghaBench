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
 scalar_t__ print_hex_buf (char**,size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*,char const*) ; 

__attribute__((used)) static int print_remainder_hex(const char* pref, uint8_t** d, size_t* dlen,
	char** s, size_t* slen)
{
	int w = 0;
	w += sldns_str_print(s, slen, "%s", pref);
	w += print_hex_buf(s, slen, *d, *dlen);
	*d += *dlen;
	*dlen = 0;
	return w;
}