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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_LABEL_OVERFLOW ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_SYNTAX ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_SYNTAX_INT ; 
 int RET_ERR (int /*<<< orphan*/ ,int) ; 
 int RET_ERR_SHIFT (int,int) ; 
 int sldns_str2wire_b64_buf (char*,scalar_t__*,size_t*) ; 
 int sldns_str2wire_hex_buf (char*,scalar_t__*,size_t*) ; 
 int /*<<< orphan*/  sldns_write_uint16 (scalar_t__*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strtol (char*,char**,int) ; 

int sldns_str2wire_hip_buf(const char* str, uint8_t* rd, size_t* len)
{
	char* s, *end;
	int e;
	size_t hitlen, pklen = 0;
	/* presentation format:
	 * 	pk-algo HIThex pubkeybase64
	 * wireformat:
	 * 	hitlen[1byte] pkalgo[1byte] pubkeylen[2byte] [hit] [pubkey] */
	if(*len < 4)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;

	/* read PK algorithm */
	rd[1] = (uint8_t)strtol((char*)str, &s, 10);
	if(*s != ' ')
		return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX_INT, s-(char*)str);
	s++;
	while(*s == ' ')
		s++;

	/* read HIT hex tag */
	/* zero terminate the tag (replace later) */
	end = strchr(s, ' ');
	if(!end) return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX, s-(char*)str);
	*end = 0;
	hitlen = *len - 4;
	if((e = sldns_str2wire_hex_buf(s, rd+4, &hitlen)) != 0) {
		*end = ' ';
		return RET_ERR_SHIFT(e, s-(char*)str);
	}
	if(hitlen > 255) {
		*end = ' ';
		return RET_ERR(LDNS_WIREPARSE_ERR_LABEL_OVERFLOW, s-(char*)str+255*2);
	}
	rd[0] = (uint8_t)hitlen;
	*end = ' ';
	s = end+1;

	/* read pubkey base64 sequence */
	pklen = *len - 4 - hitlen;
	if((e = sldns_str2wire_b64_buf(s, rd+4+hitlen, &pklen)) != 0)
		return RET_ERR_SHIFT(e, s-(char*)str);
	if(pklen > 65535)
		return RET_ERR(LDNS_WIREPARSE_ERR_LABEL_OVERFLOW, s-(char*)str+65535);
	sldns_write_uint16(rd+2, (uint16_t)pklen);

	*len = 4 + hitlen + pklen;
	return LDNS_WIREPARSE_ERR_OK;
}