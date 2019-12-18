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
typedef  int /*<<< orphan*/  sldns_rdf_type ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int sldns_bget_token_par (int /*<<< orphan*/ *,char*,char*,size_t,int*,char*) ; 
 char* sldns_buffer_current (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_position (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sldns_rdf_type_maybe_quoted (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
sldns_parse_rdf_token(sldns_buffer* strbuf, char* token, size_t token_len,
	int* quoted, int* parens, size_t* pre_data_pos,
	const char* delimiters, sldns_rdf_type rdftype, size_t* token_strlen)
{
	size_t slen;

	/* skip spaces */
	while(sldns_buffer_remaining(strbuf) > 0 && !*quoted &&
		*(sldns_buffer_current(strbuf)) == ' ') {
		sldns_buffer_skip(strbuf, 1);
	}

	*pre_data_pos = sldns_buffer_position(strbuf);
	if(sldns_bget_token_par(strbuf, token, (*quoted)?"\"":delimiters,
		token_len, parens, (*quoted)?NULL:" \t") == -1) {
		return 0;
	}
	slen = strlen(token);
	/* check if not quoted yet, and we have encountered quotes */
	if(!*quoted && sldns_rdf_type_maybe_quoted(rdftype) &&
		slen >= 2 &&
		(token[0] == '"' || token[0] == '\'') && 
		(token[slen-1] == '"' || token[slen-1] == '\'')) {
		/* move token two smaller (quotes) with endnull */
		memmove(token, token+1, slen-2);
		token[slen-2] = 0;
		slen -= 2;
		*quoted = 1;
	} else if(!*quoted && sldns_rdf_type_maybe_quoted(rdftype) &&
		slen >= 2 &&
		(token[0] == '"' || token[0] == '\'')) {
		/* got the start quote (remove it) but read remainder
		 * of quoted string as well into remainder of token */
		memmove(token, token+1, slen-1);
		token[slen-1] = 0;
		slen -= 1;
		*quoted = 1;
		/* rewind buffer over skipped whitespace */
		while(sldns_buffer_position(strbuf) > 0 &&
			(sldns_buffer_current(strbuf)[-1] == ' ' ||
			sldns_buffer_current(strbuf)[-1] == '\t')) {
			sldns_buffer_skip(strbuf, -1);
		}
		if(sldns_bget_token_par(strbuf, token+slen,
			"\"", token_len-slen,
			parens, NULL) == -1) {
			return 0;
		}
		slen = strlen(token);
	}
	*token_strlen = slen;
	return 1;
}