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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int LDNS_WIREPARSE_ERR_SYNTAX_HEX ; 
 int RET_ERR (int,int) ; 
 scalar_t__ isxdigit (unsigned char) ; 
 int sldns_hexdigit_to_int (char const) ; 
 scalar_t__ strlen (char const*) ; 

int sldns_str2wire_nsec3_salt_buf(const char* str, uint8_t* rd, size_t* len)
{
	int i, salt_length_str = (int)strlen(str);
	if (salt_length_str == 1 && str[0] == '-') {
		salt_length_str = 0;
	} else if (salt_length_str % 2 != 0) {
		return LDNS_WIREPARSE_ERR_SYNTAX_HEX;
	}
	if (salt_length_str > 512)
		return LDNS_WIREPARSE_ERR_SYNTAX_HEX;
	if(*len < 1+(size_t)salt_length_str / 2)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	rd[0] = (uint8_t) (salt_length_str / 2);
	for (i = 0; i < salt_length_str; i += 2) {
		if (isxdigit((unsigned char)str[i]) &&
			isxdigit((unsigned char)str[i+1])) {
			rd[1+i/2] = (uint8_t)(sldns_hexdigit_to_int(str[i])*16
				+ sldns_hexdigit_to_int(str[i+1]));
		} else {
			return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX_HEX, i);
		}
	}
	*len = 1 + (size_t)rd[0];
	return LDNS_WIREPARSE_ERR_OK;
}