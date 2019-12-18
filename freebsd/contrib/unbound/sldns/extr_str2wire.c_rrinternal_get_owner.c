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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_SYNTAX ; 
 int RET_ERR (int /*<<< orphan*/ ,scalar_t__) ; 
 int RET_ERR_SHIFT (int,scalar_t__) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int sldns_bget_token (int /*<<< orphan*/ *,char*,char*,size_t) ; 
 scalar_t__ sldns_buffer_position (int /*<<< orphan*/ *) ; 
 int sldns_str2wire_dname_buf_origin (char*,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
rrinternal_get_owner(sldns_buffer* strbuf, uint8_t* rr, size_t* len,
	size_t* dname_len, uint8_t* origin, size_t origin_len, uint8_t* prev,
	size_t prev_len, char* token, size_t token_len)
{
	/* split the rr in its parts -1 signals trouble */
	if(sldns_bget_token(strbuf, token, "\t\n ", token_len) == -1) {
		return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX,
			sldns_buffer_position(strbuf));
	}

	if(strcmp(token, "@") == 0) {
		uint8_t* tocopy;
		if (origin) {
			*dname_len = origin_len;
			tocopy = origin;
		} else if (prev) {
			*dname_len = prev_len;
			tocopy = prev;
		} else {
			/* default to root */
			*dname_len = 1;
			tocopy = (uint8_t*)"\0";
		}
		if(*len < *dname_len)
			return RET_ERR(LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL,
				sldns_buffer_position(strbuf));
		memmove(rr, tocopy, *dname_len);
	} else if(*token == '\0') {
		/* no ownername was given, try prev, if that fails
		 * origin, else default to root */
		uint8_t* tocopy;
		if(prev) {
			*dname_len = prev_len;
			tocopy = prev;
		} else if(origin) {
			*dname_len = origin_len;
			tocopy = origin;
		} else {
			*dname_len = 1;
			tocopy = (uint8_t*)"\0";
		}
		if(*len < *dname_len)
			return RET_ERR(LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL,
				sldns_buffer_position(strbuf));
		memmove(rr, tocopy, *dname_len);
	} else {
		size_t dlen = *len;
		int s = sldns_str2wire_dname_buf_origin(token, rr, &dlen,
			origin, origin_len);
		if(s) return RET_ERR_SHIFT(s,
			sldns_buffer_position(strbuf)-strlen(token));
		*dname_len = dlen;
	}
	return LDNS_WIREPARSE_ERR_OK;
}