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
typedef  int /*<<< orphan*/  jsmntok_t ;
typedef  int /*<<< orphan*/  jsmn_parser ;

/* Variables and functions */
 int /*<<< orphan*/  JSMN_OBJECT ; 
 int /*<<< orphan*/  JSMN_PRIMITIVE ; 
 int /*<<< orphan*/  JSMN_STRING ; 
 int TOKEN_EQ (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int TOKEN_STRING (char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  check (int) ; 
 int /*<<< orphan*/  jsmn_init (int /*<<< orphan*/ *) ; 
 int jsmn_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int test_simple() {
	const char *js;
	int r;
	jsmn_parser p;
	jsmntok_t tokens[10];

	js = "{\"a\": 0}";

	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r >= 0);
	check(TOKEN_EQ(tokens[0], 0, 8, JSMN_OBJECT));
	check(TOKEN_EQ(tokens[1], 2, 3, JSMN_STRING));
	check(TOKEN_EQ(tokens[2], 6, 7, JSMN_PRIMITIVE));

	check(TOKEN_STRING(js, tokens[0], js));
	check(TOKEN_STRING(js, tokens[1], "a"));
	check(TOKEN_STRING(js, tokens[2], "0"));

	jsmn_init(&p);
	js = "[\"a\":{},\"b\":{}]";
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r >= 0);

	jsmn_init(&p);
	js = "{\n \"Day\": 26,\n \"Month\": 9,\n \"Year\": 12\n }";
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r >= 0);

	return 0;
}