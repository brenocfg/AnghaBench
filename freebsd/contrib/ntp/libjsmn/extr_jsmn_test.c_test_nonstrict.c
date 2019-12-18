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
 int TOKEN_STRING (char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check (int) ; 
 int /*<<< orphan*/  jsmn_init (int /*<<< orphan*/ *) ; 
 int jsmn_parse (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int) ; 
 int strlen (char const*) ; 

int test_nonstrict() {
	const char *js;
	int r;
	jsmn_parser p;
	jsmntok_t tokens[10];

	js = "a: 0garbage";

	jsmn_init(&p);
	r = jsmn_parse(&p, js, 4, tokens, 10);
	check(r == 2);
	check(TOKEN_STRING(js, tokens[0], "a"));
	check(TOKEN_STRING(js, tokens[1], "0"));

	js = "Day : 26\nMonth : Sep\n\nYear: 12";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == 6);
	return 0;
}