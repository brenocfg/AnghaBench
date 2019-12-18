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
 int JSMN_ERROR_INVAL ; 
 int /*<<< orphan*/  check (int) ; 
 int /*<<< orphan*/  jsmn_init (int /*<<< orphan*/ *) ; 
 int jsmn_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int test_objects_arrays() {
	int r;
	jsmn_parser p;
	jsmntok_t tokens[10];
	const char *js;

	js = "[10}";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == JSMN_ERROR_INVAL);

	js = "[10]";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r >= 0);

	js = "{\"a\": 1]";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == JSMN_ERROR_INVAL);

	js = "{\"a\": 1}";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r >= 0);

	return 0;
}