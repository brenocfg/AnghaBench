#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* buf; } ;
struct json_writer {TYPE_1__ json; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 struct json_writer JSON_WRITER_INIT ; 
 int MAX_LINE_LENGTH ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  get_d (int,double*) ; 
 int /*<<< orphan*/  get_i (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_s (int,char**) ; 
 char* get_trimmed_line (char*,int) ; 
 int /*<<< orphan*/  jw_array_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_array_double (struct json_writer*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  jw_array_false (struct json_writer*) ; 
 int /*<<< orphan*/  jw_array_inline_begin_array (struct json_writer*) ; 
 int /*<<< orphan*/  jw_array_inline_begin_object (struct json_writer*) ; 
 int /*<<< orphan*/  jw_array_intmax (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_array_null (struct json_writer*) ; 
 int /*<<< orphan*/  jw_array_string (struct json_writer*,char*) ; 
 int /*<<< orphan*/  jw_array_true (struct json_writer*) ; 
 int /*<<< orphan*/  jw_end (struct json_writer*) ; 
 int /*<<< orphan*/  jw_is_terminated (struct json_writer*) ; 
 int /*<<< orphan*/  jw_object_begin (struct json_writer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_double (struct json_writer*,char*,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  jw_object_false (struct json_writer*,char*) ; 
 int /*<<< orphan*/  jw_object_inline_begin_array (struct json_writer*,char*) ; 
 int /*<<< orphan*/  jw_object_inline_begin_object (struct json_writer*,char*) ; 
 int /*<<< orphan*/  jw_object_intmax (struct json_writer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jw_object_null (struct json_writer*,char*) ; 
 int /*<<< orphan*/  jw_object_string (struct json_writer*,char*,char*) ; 
 int /*<<< orphan*/  jw_object_true (struct json_writer*,char*) ; 
 int /*<<< orphan*/  pretty ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static int scripted(void)
{
	struct json_writer jw = JSON_WRITER_INIT;
	char buf[MAX_LINE_LENGTH];
	char *line;
	int line_nr = 0;

	line = get_trimmed_line(buf, MAX_LINE_LENGTH);
	if (!line)
		return 0;

	if (!strcmp(line, "object"))
		jw_object_begin(&jw, pretty);
	else if (!strcmp(line, "array"))
		jw_array_begin(&jw, pretty);
	else
		die("expected first line to be 'object' or 'array'");

	while ((line = get_trimmed_line(buf, MAX_LINE_LENGTH)) != NULL) {
		char *verb;
		char *key;
		char *s_value;
		intmax_t i_value;
		double d_value;

		line_nr++;

		verb = strtok(line, " ");

		if (!strcmp(verb, "end")) {
			jw_end(&jw);
		}
		else if (!strcmp(verb, "object-string")) {
			get_s(line_nr, &key);
			get_s(line_nr, &s_value);
			jw_object_string(&jw, key, s_value);
		}
		else if (!strcmp(verb, "object-int")) {
			get_s(line_nr, &key);
			get_i(line_nr, &i_value);
			jw_object_intmax(&jw, key, i_value);
		}
		else if (!strcmp(verb, "object-double")) {
			get_s(line_nr, &key);
			get_i(line_nr, &i_value);
			get_d(line_nr, &d_value);
			jw_object_double(&jw, key, i_value, d_value);
		}
		else if (!strcmp(verb, "object-true")) {
			get_s(line_nr, &key);
			jw_object_true(&jw, key);
		}
		else if (!strcmp(verb, "object-false")) {
			get_s(line_nr, &key);
			jw_object_false(&jw, key);
		}
		else if (!strcmp(verb, "object-null")) {
			get_s(line_nr, &key);
			jw_object_null(&jw, key);
		}
		else if (!strcmp(verb, "object-object")) {
			get_s(line_nr, &key);
			jw_object_inline_begin_object(&jw, key);
		}
		else if (!strcmp(verb, "object-array")) {
			get_s(line_nr, &key);
			jw_object_inline_begin_array(&jw, key);
		}
		else if (!strcmp(verb, "array-string")) {
			get_s(line_nr, &s_value);
			jw_array_string(&jw, s_value);
		}
		else if (!strcmp(verb, "array-int")) {
			get_i(line_nr, &i_value);
			jw_array_intmax(&jw, i_value);
		}
		else if (!strcmp(verb, "array-double")) {
			get_i(line_nr, &i_value);
			get_d(line_nr, &d_value);
			jw_array_double(&jw, i_value, d_value);
		}
		else if (!strcmp(verb, "array-true"))
			jw_array_true(&jw);
		else if (!strcmp(verb, "array-false"))
			jw_array_false(&jw);
		else if (!strcmp(verb, "array-null"))
			jw_array_null(&jw);
		else if (!strcmp(verb, "array-object"))
			jw_array_inline_begin_object(&jw);
		else if (!strcmp(verb, "array-array"))
			jw_array_inline_begin_array(&jw);
		else
			die("unrecognized token: '%s'", verb);
	}

	if (!jw_is_terminated(&jw))
		die("json not terminated: '%s'", jw.json.buf);

	printf("%s\n", jw.json.buf);

	strbuf_release(&jw.json);
	return 0;
}