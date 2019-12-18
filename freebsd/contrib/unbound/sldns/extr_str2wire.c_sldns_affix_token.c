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
 int /*<<< orphan*/  sldns_parse_rdf_token (int /*<<< orphan*/ *,char*,size_t,int*,int*,size_t*,char const*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
sldns_affix_token(sldns_buffer* strbuf, char* token, size_t* token_len,
	int* quoted, int* parens, size_t* pre_data_pos,
	const char* delimiters, sldns_rdf_type rdftype, size_t* token_strlen)
{
	size_t addlen = *token_len - *token_strlen;
	size_t addstrlen = 0;

	/* add space */
	if(addlen < 1) return 0;
	token[*token_strlen] = ' ';
	token[++(*token_strlen)] = 0;

	/* read another token */
	addlen = *token_len - *token_strlen;
	if(!sldns_parse_rdf_token(strbuf, token+*token_strlen, addlen, quoted,
		parens, pre_data_pos, delimiters, rdftype, &addstrlen))
		return 0;
	(*token_strlen) += addstrlen;
	return 1;
}