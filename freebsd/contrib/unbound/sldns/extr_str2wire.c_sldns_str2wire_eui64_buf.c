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
typedef  unsigned int uint8_t ;

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int LDNS_WIREPARSE_ERR_SYNTAX_EUI64 ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,int*) ; 
 scalar_t__ strlen (char const*) ; 

int sldns_str2wire_eui64_buf(const char* str, uint8_t* rd, size_t* len)
{
	unsigned int a, b, c, d, e, f, g, h;
	int l;

	if(*len < 8)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	if (sscanf(str, "%2x-%2x-%2x-%2x-%2x-%2x-%2x-%2x%n",
			&a, &b, &c, &d, &e, &f, &g, &h, &l) != 8 ||
			l != (int)strlen(str))
		return LDNS_WIREPARSE_ERR_SYNTAX_EUI64;
	rd[0] = a;
	rd[1] = b;
	rd[2] = c;
	rd[3] = d;
	rd[4] = e;
	rd[5] = f;
	rd[6] = g;
	rd[7] = h;
	*len = 8;
	return LDNS_WIREPARSE_ERR_OK;
}