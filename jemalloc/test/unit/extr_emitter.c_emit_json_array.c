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
 int /*<<< orphan*/  emitter_json_key (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  emitter_json_kv (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emitter_json_object_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_object_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emitter_type_int ; 

__attribute__((used)) static void
emit_json_array(emitter_t *emitter) {
	int ival = 123;

	emitter_begin(emitter);
	emitter_json_key(emitter, "dict");
	emitter_json_object_begin(emitter);
	emitter_json_key(emitter, "arr");
	emitter_json_array_begin(emitter);
	emitter_json_object_begin(emitter);
	emitter_json_kv(emitter, "foo", emitter_type_int, &ival);
	emitter_json_object_end(emitter); /* Close arr[0] */
	/* arr[1] and arr[2] are primitives. */
	emitter_json_value(emitter, emitter_type_int, &ival);
	emitter_json_value(emitter, emitter_type_int, &ival);
	emitter_json_object_begin(emitter);
	emitter_json_kv(emitter, "bar", emitter_type_int, &ival);
	emitter_json_kv(emitter, "baz", emitter_type_int, &ival);
	emitter_json_object_end(emitter); /* Close arr[3]. */
	emitter_json_array_end(emitter); /* Close arr. */
	emitter_json_object_end(emitter); /* Close dict. */
	emitter_end(emitter);
}