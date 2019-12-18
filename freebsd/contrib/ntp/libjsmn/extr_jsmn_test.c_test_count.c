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
typedef  int /*<<< orphan*/  jsmn_parser ;

/* Variables and functions */
 int /*<<< orphan*/  check (int) ; 
 int /*<<< orphan*/  jsmn_init (int /*<<< orphan*/ *) ; 
 int jsmn_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int test_count() {
	jsmn_parser p;
	const char *js;

	js = "{}";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 1);

	js = "[]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 1);

	js = "[[]]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 2);

	js = "[[], []]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 3);

	js = "[[], []]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 3);

	js = "[[], [[]], [[], []]]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 7);

	js = "[\"a\", [[], []]]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 5);

	js = "[[], \"[], [[]]\", [[]]]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 5);

	js = "[1, 2, 3]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 4);

	js = "[1, 2, [3, \"a\"], null]";
	jsmn_init(&p);
	check(jsmn_parse(&p, js, strlen(js), NULL, 0) == 7);

	return 0;
}