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

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_LABEL_OVERFLOW ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int LDNS_WIREPARSE_ERR_SYNTAX_B64 ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_SYNTAX_INT ; 
 int RET_ERR (int /*<<< orphan*/ ,int) ; 
 int sldns_b64_pton (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_write_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strtol (char const*,char**,int) ; 

int sldns_str2wire_int16_data_buf(const char* str, uint8_t* rd, size_t* len)
{
	char* s;
	int n;
	n = strtol(str, &s, 10);
	if(*len < ((size_t)n)+2)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	if(n > 65535)
		return LDNS_WIREPARSE_ERR_LABEL_OVERFLOW;

	if(n == 0) {
		sldns_write_uint16(rd, 0);
		*len = 2;
		return LDNS_WIREPARSE_ERR_OK;
	}
	if(*s != ' ')
		return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX_INT, s-(char*)str);
	s++;
	while(*s == ' ')
		s++;

	n = sldns_b64_pton(s, rd+2, (*len)-2);
	if(n < 0)
		return LDNS_WIREPARSE_ERR_SYNTAX_B64;
	sldns_write_uint16(rd, (uint16_t)n);
	*len = ((size_t)n)+2;
	return LDNS_WIREPARSE_ERR_OK;
}