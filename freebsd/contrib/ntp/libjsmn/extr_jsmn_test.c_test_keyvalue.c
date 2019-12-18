#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; } ;
typedef  TYPE_1__ jsmntok_t ;
typedef  int /*<<< orphan*/  jsmn_parser ;

/* Variables and functions */
 int JSMN_ERROR_INVAL ; 
 int /*<<< orphan*/  check (int) ; 
 int /*<<< orphan*/  jsmn_init (int /*<<< orphan*/ *) ; 
 int jsmn_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int test_keyvalue() {
	const char *js;
	int r;
	jsmn_parser p;
	jsmntok_t tokens[10];

	js = "{\"a\": 0, \"b\": \"c\"}";

	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == 5);
	check(tokens[0].size == 2); /* two keys */
	check(tokens[1].size == 1 && tokens[3].size == 1); /* one value per key */
	check(tokens[2].size == 0 && tokens[4].size == 0); /* values have zero size */

	js = "{\"a\"\n0}";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == JSMN_ERROR_INVAL);

	js = "{\"a\", 0}";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == JSMN_ERROR_INVAL);

	js = "{\"a\": {2}}";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == JSMN_ERROR_INVAL);

	js = "{\"a\": {2: 3}}";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == JSMN_ERROR_INVAL);


	js = "{\"a\": {\"a\": 2 3}}";
	jsmn_init(&p);
	r = jsmn_parse(&p, js, strlen(js), tokens, 10);
	check(r == JSMN_ERROR_INVAL);
	return 0;
}