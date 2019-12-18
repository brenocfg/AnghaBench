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
 int /*<<< orphan*/  emitter_table_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
emit_table_printf(emitter_t *emitter) {
	emitter_begin(emitter);
	emitter_table_printf(emitter, "Table note 1\n");
	emitter_table_printf(emitter, "Table note 2 %s\n",
	    "with format string");
	emitter_end(emitter);
}