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
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ jsmntok_t ;
typedef  int /*<<< orphan*/  jsmn_parser ;

/* Variables and functions */
 scalar_t__ JSMN_STRING ; 
 int TOKEN_STRING (char const*,TYPE_1__,char*) ; 
 int /*<<< orphan*/  check (int) ; 
 int /*<<< orphan*/  jsmn_init (int /*<<< orphan*/ *) ; 
 int jsmn_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int test_string() {
	int r;
	jsmn_parser p;
	jsmntok_t tok[10];
	const char *js;

	js = "\"strVar\" : \"hello world\"";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tok, 10);
	check(r >= 0 && tok[0].type == JSMN_STRING
			&& tok[1].type == JSMN_STRING);
	check(TOKEN_STRING(js, tok[0], "strVar"));
	check(TOKEN_STRING(js, tok[1], "hello world"));

	js = "\"strVar\" : \"escapes: \\/\\r\\n\\t\\b\\f\\\"\\\\\"";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tok, 10);
	check(r >= 0 && tok[0].type == JSMN_STRING
			&& tok[1].type == JSMN_STRING);
	check(TOKEN_STRING(js, tok[0], "strVar"));
	check(TOKEN_STRING(js, tok[1], "escapes: \\/\\r\\n\\t\\b\\f\\\"\\\\"));

	js = "\"strVar\" : \"\"";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tok, 10);
	check(r >= 0 && tok[0].type == JSMN_STRING
			&& tok[1].type == JSMN_STRING);
	check(TOKEN_STRING(js, tok[0], "strVar"));
	check(TOKEN_STRING(js, tok[1], ""));

	return 0;
}