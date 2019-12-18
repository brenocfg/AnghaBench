#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsmntok_t ;
typedef  int /*<<< orphan*/  jsmnerr_t ;
struct TYPE_4__ {int pos; } ;
typedef  TYPE_1__ jsmn_parser ;

/* Variables and functions */
 int /*<<< orphan*/  JSMN_ERROR_INVAL ; 
 int /*<<< orphan*/  JSMN_ERROR_NOMEM ; 
 int /*<<< orphan*/  JSMN_ERROR_PART ; 
 int /*<<< orphan*/  JSMN_STRING ; 
 int /*<<< orphan*/  JSMN_SUCCESS ; 
 int /*<<< orphan*/ * jsmn_alloc_token (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  jsmn_fill_token (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static jsmnerr_t jsmn_parse_string(jsmn_parser *parser, const char *js,
				   size_t len,
				   jsmntok_t *tokens, size_t num_tokens)
{
	jsmntok_t *token;
	int start = parser->pos;

	/* Skip starting quote */
	parser->pos++;

	for (; parser->pos < len; parser->pos++) {
		char c = js[parser->pos];

		/* Quote: end of string */
		if (c == '\"') {
			token = jsmn_alloc_token(parser, tokens, num_tokens);
			if (token == NULL) {
				parser->pos = start;
				return JSMN_ERROR_NOMEM;
			}
			jsmn_fill_token(token, JSMN_STRING, start+1,
					parser->pos);
			return JSMN_SUCCESS;
		}

		/* Backslash: Quoted symbol expected */
		if (c == '\\') {
			parser->pos++;
			switch (js[parser->pos]) {
				/* Allowed escaped symbols */
			case '\"':
			case '/':
			case '\\':
			case 'b':
			case 'f':
			case 'r':
			case 'n':
			case 't':
				break;
				/* Allows escaped symbol \uXXXX */
			case 'u':
				/* TODO */
				break;
				/* Unexpected symbol */
			default:
				parser->pos = start;
				return JSMN_ERROR_INVAL;
			}
		}
	}
	parser->pos = start;
	return JSMN_ERROR_PART;
}