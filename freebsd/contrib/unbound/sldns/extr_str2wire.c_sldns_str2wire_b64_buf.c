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
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int LDNS_WIREPARSE_ERR_SYNTAX_B64 ; 
 int sldns_b64_pton (char const*,int /*<<< orphan*/ *,size_t) ; 
 size_t sldns_b64_pton_calculate_size (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int sldns_str2wire_b64_buf(const char* str, uint8_t* rd, size_t* len)
{
	size_t sz = sldns_b64_pton_calculate_size(strlen(str));
	int n;
	if(strcmp(str, "0") == 0) {
		*len = 0;
		return LDNS_WIREPARSE_ERR_OK;
	}
	if(*len < sz)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	n = sldns_b64_pton(str, rd, *len);
	if(n < 0)
		return LDNS_WIREPARSE_ERR_SYNTAX_B64;
	*len = (size_t)n;
	return LDNS_WIREPARSE_ERR_OK;
}