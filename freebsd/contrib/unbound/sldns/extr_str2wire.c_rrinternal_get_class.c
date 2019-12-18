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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_RR_CLASS_IN ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_SYNTAX_CLASS ; 
 int RET_ERR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sldns_bget_token (int /*<<< orphan*/ *,char*,char*,size_t) ; 
 int /*<<< orphan*/  sldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_get_rr_class_by_name (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
rrinternal_get_class(sldns_buffer* strbuf, char* token, size_t token_len,
	int* not_there, uint16_t* cl)
{
	/* if 'not_there' then we got token from previous parse routine */
	if(!*not_there) {
		/* parse new token for class */
		if(sldns_bget_token(strbuf, token, "\t\n ", token_len) == -1) {
			return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX_CLASS,
				sldns_buffer_position(strbuf));
		}
	} else *not_there = 0;
	*cl = sldns_get_rr_class_by_name(token);
	/* class can be left out too, assume IN, current token must be type */
	if(*cl == 0 && strcmp(token, "CLASS0") != 0) {
		*not_there = 1;
		*cl = LDNS_RR_CLASS_IN;
	}
	return LDNS_WIREPARSE_ERR_OK;
}