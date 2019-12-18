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
typedef  int /*<<< orphan*/  emitter_t ;

/* Variables and functions */
 int /*<<< orphan*/  emitter_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_array_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_array_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  emitter_type_int ; 
 int /*<<< orphan*/  emitter_type_string ; 

__attribute__((used)) static void
emit_json_nested_array(emitter_t *emitter) {
	int ival = 123;
	char *sval = "foo";
	emitter_begin(emitter);
	emitter_json_array_begin(emitter);
		emitter_json_array_begin(emitter);
		emitter_json_value(emitter, emitter_type_int, &ival);
		emitter_json_value(emitter, emitter_type_string, &sval);
		emitter_json_value(emitter, emitter_type_int, &ival);
		emitter_json_value(emitter, emitter_type_string, &sval);
		emitter_json_array_end(emitter);
		emitter_json_array_begin(emitter);
		emitter_json_value(emitter, emitter_type_int, &ival);
		emitter_json_array_end(emitter);
		emitter_json_array_begin(emitter);
		emitter_json_value(emitter, emitter_type_string, &sval);
		emitter_json_value(emitter, emitter_type_int, &ival);
		emitter_json_array_end(emitter);
		emitter_json_array_begin(emitter);
		emitter_json_array_end(emitter);
	emitter_json_array_end(emitter);
	emitter_end(emitter);
}