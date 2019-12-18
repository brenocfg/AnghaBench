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
 int /*<<< orphan*/  emitter_dict_begin (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  emitter_dict_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_key (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  emitter_json_kv (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emitter_json_object_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_json_object_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_kv (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emitter_table_dict_begin (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  emitter_table_dict_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitter_table_kv (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emitter_type_int ; 

__attribute__((used)) static void
emit_modal(emitter_t *emitter) {
	int val = 123;
	emitter_begin(emitter);
	emitter_dict_begin(emitter, "j0", "T0");
	emitter_json_key(emitter, "j1");
	emitter_json_object_begin(emitter);
	emitter_kv(emitter, "i1", "I1", emitter_type_int, &val);
	emitter_json_kv(emitter, "i2", emitter_type_int, &val);
	emitter_table_kv(emitter, "I3", emitter_type_int, &val);
	emitter_table_dict_begin(emitter, "T1");
	emitter_kv(emitter, "i4", "I4", emitter_type_int, &val);
	emitter_json_object_end(emitter); /* Close j1 */
	emitter_kv(emitter, "i5", "I5", emitter_type_int, &val);
	emitter_table_dict_end(emitter); /* Close T1 */
	emitter_kv(emitter, "i6", "I6", emitter_type_int, &val);
	emitter_dict_end(emitter); /* Close j0 / T0 */
	emitter_end(emitter);
}