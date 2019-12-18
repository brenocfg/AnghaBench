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
 int LDNS_WIREPARSE_ERR_SYNTAX_TAG ; 
 int RET_ERR (int,int) ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int sldns_str2wire_tag_buf(const char* str, uint8_t* rd, size_t* len)
{
	size_t slen = strlen(str);
	const char* ptr;

	if (slen > 255)
		return LDNS_WIREPARSE_ERR_SYNTAX_TAG;
	if(*len < slen+1)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	for (ptr = str; *ptr; ptr++) {
		if(!isalnum((unsigned char)*ptr))
			return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX_TAG, ptr-str);
	}
	rd[0] = (uint8_t)slen;
	memmove(rd+1, str, slen);
	*len = slen+1;
	return LDNS_WIREPARSE_ERR_OK;
}