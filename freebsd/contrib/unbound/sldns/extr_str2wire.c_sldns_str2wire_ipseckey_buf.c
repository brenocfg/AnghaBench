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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  token ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_INVALID_STR ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int RET_ERR (int,int /*<<< orphan*/ ) ; 
 int RET_ERR_SHIFT (int,int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (char*) ; 
 scalar_t__ sldns_bget_token (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ sldns_buffer_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_init_frm_data (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_str2wire_a_buf (char*,int*,size_t*) ; 
 int sldns_str2wire_aaaa_buf (char*,int*,size_t*) ; 
 int sldns_str2wire_b64_buf (char const*,int*,size_t*) ; 
 int sldns_str2wire_dname_buf (char*,int*,size_t*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int sldns_str2wire_ipseckey_buf(const char* str, uint8_t* rd, size_t* len)
{
	size_t gwlen = 0, keylen = 0;
	int s;
	uint8_t gwtype;
	char token[512];
	sldns_buffer strbuf;
	sldns_buffer_init_frm_data(&strbuf, (uint8_t*)str, strlen(str));

	if(*len < 3)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	/* precedence */
	if(sldns_bget_token(&strbuf, token, "\t\n ", sizeof(token)) <= 0)
		return RET_ERR(LDNS_WIREPARSE_ERR_INVALID_STR,
			sldns_buffer_position(&strbuf));
	rd[0] = (uint8_t)atoi(token);
	/* gateway_type */
	if(sldns_bget_token(&strbuf, token, "\t\n ", sizeof(token)) <= 0)
		return RET_ERR(LDNS_WIREPARSE_ERR_INVALID_STR,
			sldns_buffer_position(&strbuf));
	rd[1] = (uint8_t)atoi(token);
	gwtype = rd[1];
	/* algorithm */
	if(sldns_bget_token(&strbuf, token, "\t\n ", sizeof(token)) <= 0)
		return RET_ERR(LDNS_WIREPARSE_ERR_INVALID_STR,
			sldns_buffer_position(&strbuf));
	rd[2] = (uint8_t)atoi(token);

	/* gateway */
	if(sldns_bget_token(&strbuf, token, "\t\n ", sizeof(token)) <= 0)
		return RET_ERR(LDNS_WIREPARSE_ERR_INVALID_STR,
			sldns_buffer_position(&strbuf));
	if(gwtype == 0) {
		/* NOGATEWAY */
		if(strcmp(token, ".") != 0)
			return RET_ERR(LDNS_WIREPARSE_ERR_INVALID_STR,
				sldns_buffer_position(&strbuf));
		gwlen = 0;
	} else if(gwtype == 1) {
		/* IP4 */
		gwlen = *len - 3;
		s = sldns_str2wire_a_buf(token, rd+3, &gwlen);
		if(s) return RET_ERR_SHIFT(s, sldns_buffer_position(&strbuf));
	} else if(gwtype == 2) {
		/* IP6 */
		gwlen = *len - 3;
		s = sldns_str2wire_aaaa_buf(token, rd+3, &gwlen);
		if(s) return RET_ERR_SHIFT(s, sldns_buffer_position(&strbuf));
	} else if(gwtype == 3) {
		/* DNAME */
		gwlen = *len - 3;
		s = sldns_str2wire_dname_buf(token, rd+3, &gwlen);
		if(s) return RET_ERR_SHIFT(s, sldns_buffer_position(&strbuf));
	} else {
		/* unknown gateway type */
		return RET_ERR(LDNS_WIREPARSE_ERR_INVALID_STR,
			sldns_buffer_position(&strbuf));
	}
	/* double check for size */
	if(*len < 3 + gwlen)
		return RET_ERR(LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL,
			sldns_buffer_position(&strbuf));

	/* publickey in remainder of strbuf */
	keylen = *len - 3 - gwlen;
	s = sldns_str2wire_b64_buf((const char*)sldns_buffer_current(&strbuf),
		rd+3+gwlen, &keylen);
	if(s) return RET_ERR_SHIFT(s, sldns_buffer_position(&strbuf));

	*len = 3 + gwlen + keylen;
	return LDNS_WIREPARSE_ERR_OK;
}