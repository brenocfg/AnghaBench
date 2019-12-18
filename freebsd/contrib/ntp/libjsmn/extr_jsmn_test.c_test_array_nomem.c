#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  toksmall ;
typedef  int /*<<< orphan*/  toklarge ;
struct TYPE_6__ {scalar_t__ type; int size; } ;
typedef  TYPE_1__ jsmntok_t ;
typedef  int /*<<< orphan*/  jsmn_parser ;

/* Variables and functions */
 scalar_t__ JSMN_ARRAY ; 
 int JSMN_ERROR_NOMEM ; 
 int /*<<< orphan*/  check (int) ; 
 int /*<<< orphan*/  jsmn_init (int /*<<< orphan*/ *) ; 
 int jsmn_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int test_array_nomem() {
	int i;
	int r;
	jsmn_parser p;
	jsmntok_t toksmall[10], toklarge[10];
	const char *js;

	js = "  [ 1, true, [123, \"hello\"]]";

	for (i = 0; i < 6; i++) {
		jsmn_init(&p);
		memset(toksmall, 0, sizeof(toksmall));
		memset(toklarge, 0, sizeof(toklarge));
		r = jsmn_parse(&p, js, strlen(js), toksmall, i);
		check(r == JSMN_ERROR_NOMEM);

		memcpy(toklarge, toksmall, sizeof(toksmall));

		r = jsmn_parse(&p, js, strlen(js), toklarge, 10);
		check(r >= 0);

		check(toklarge[0].type == JSMN_ARRAY && toklarge[0].size == 3);
		check(toklarge[3].type == JSMN_ARRAY && toklarge[3].size == 2);
	}
	return 0;
}