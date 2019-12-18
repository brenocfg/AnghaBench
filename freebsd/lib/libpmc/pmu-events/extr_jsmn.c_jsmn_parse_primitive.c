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
 int /*<<< orphan*/  JSMN_PRIMITIVE ; 
 int /*<<< orphan*/  JSMN_SUCCESS ; 
 int /*<<< orphan*/ * jsmn_alloc_token (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  jsmn_fill_token (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static jsmnerr_t jsmn_parse_primitive(jsmn_parser *parser, const char *js,
				      size_t len,
				      jsmntok_t *tokens, size_t num_tokens)
{
	jsmntok_t *token;
	int start;

	start = parser->pos;

	for (; parser->pos < len; parser->pos++) {
		switch (js[parser->pos]) {
#ifndef JSMN_STRICT
		/*
		 * In strict mode primitive must be followed by ","
		 * or "}" or "]"
		 */
		case ':':
#endif
		case '\t':
		case '\r':
		case '\n':
		case ' ':
		case ',':
		case ']':
		case '}':
			goto found;
		default:
			break;
		}
		if (js[parser->pos] < 32 || js[parser->pos] >= 127) {
			parser->pos = start;
			return JSMN_ERROR_INVAL;
		}
	}
#ifdef JSMN_STRICT
	/*
	 * In strict mode primitive must be followed by a
	 * comma/object/array.
	 */
	parser->pos = start;
	return JSMN_ERROR_PART;
#endif

found:
	token = jsmn_alloc_token(parser, tokens, num_tokens);
	if (token == NULL) {
		parser->pos = start;
		return JSMN_ERROR_NOMEM;
	}
	jsmn_fill_token(token, JSMN_PRIMITIVE, start, parser->pos);
	parser->pos--; /* parent sees closing brackets */
	return JSMN_SUCCESS;
}