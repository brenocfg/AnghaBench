#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_1__ jsmntok_t ;
struct TYPE_8__ {int toknext; } ;
typedef  TYPE_2__ jsmn_parser ;
typedef  int /*<<< orphan*/  js_unicode ;
typedef  int /*<<< orphan*/  js_slash ;

/* Variables and functions */
 int JSMN_ERROR_PART ; 
 scalar_t__ JSMN_STRING ; 
 int TOKEN_STRING (char const*,TYPE_1__,char*) ; 
 int /*<<< orphan*/  check (int) ; 
 int /*<<< orphan*/  jsmn_init (TYPE_2__*) ; 
 int jsmn_parse (TYPE_2__*,char const*,int,TYPE_1__*,int) ; 
 int strlen (char const*) ; 

int test_partial_string() {
	int r;
	jsmn_parser p;
	jsmntok_t tok[10];
	const char *js;

	jsmn_init(&p);
	js = "\"x\": \"va";
	r = jsmn_parse(&p, js, strlen(js), tok, 10);
	check(r == JSMN_ERROR_PART && tok[0].type == JSMN_STRING);
	check(TOKEN_STRING(js, tok[0], "x"));
	check(p.toknext == 1);

	jsmn_init(&p);
	char js_slash[9] = "\"x\": \"va\\";
	r = jsmn_parse(&p, js_slash, sizeof(js_slash), tok, 10);
	check(r == JSMN_ERROR_PART);

	jsmn_init(&p);
	char js_unicode[10] = "\"x\": \"va\\u";
	r = jsmn_parse(&p, js_unicode, sizeof(js_unicode), tok, 10);
	check(r == JSMN_ERROR_PART);

	js = "\"x\": \"valu";
	r = jsmn_parse(&p, js, strlen(js), tok, 10);
	check(r == JSMN_ERROR_PART && tok[0].type == JSMN_STRING);
	check(TOKEN_STRING(js, tok[0], "x"));
	check(p.toknext == 1);

	js = "\"x\": \"value\"";
	r = jsmn_parse(&p, js, strlen(js), tok, 10);
	check(r >= 0 && tok[0].type == JSMN_STRING
			&& tok[1].type == JSMN_STRING);
	check(TOKEN_STRING(js, tok[0], "x"));
	check(TOKEN_STRING(js, tok[1], "value"));

	js = "\"x\": \"value\", \"y\": \"value y\"";
	r = jsmn_parse(&p, js, strlen(js), tok, 10);
	check(r >= 0 && tok[0].type == JSMN_STRING
			&& tok[1].type == JSMN_STRING && tok[2].type == JSMN_STRING
			&& tok[3].type == JSMN_STRING);
	check(TOKEN_STRING(js, tok[0], "x"));
	check(TOKEN_STRING(js, tok[1], "value"));
	check(TOKEN_STRING(js, tok[2], "y"));
	check(TOKEN_STRING(js, tok[3], "value y"));

	return 0;
}