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
 int /*<<< orphan*/  emitter_kv (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  emitter_type_int ; 

__attribute__((used)) static void emit_nested_dict(emitter_t *emitter) {
	int val = 123;
	emitter_begin(emitter);
	emitter_dict_begin(emitter, "json1", "Dict 1");
	emitter_dict_begin(emitter, "json2", "Dict 2");
	emitter_kv(emitter, "primitive", "A primitive", emitter_type_int, &val);
	emitter_dict_end(emitter); /* Close 2 */
	emitter_dict_begin(emitter, "json3", "Dict 3");
	emitter_dict_end(emitter); /* Close 3 */
	emitter_dict_end(emitter); /* Close 1 */
	emitter_dict_begin(emitter, "json4", "Dict 4");
	emitter_kv(emitter, "primitive", "Another primitive",
	    emitter_type_int, &val);
	emitter_dict_end(emitter); /* Close 4 */
	emitter_end(emitter);
}