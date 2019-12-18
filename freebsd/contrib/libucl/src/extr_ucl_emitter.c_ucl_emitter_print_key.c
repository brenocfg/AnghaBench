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
struct TYPE_3__ {int flags; char* key; int keylen; scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
struct ucl_emitter_functions {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* ucl_emitter_append_len ) (char*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ucl_emitter_append_character ) (char,int,int /*<<< orphan*/ ) ;} ;
struct ucl_emitter_context {scalar_t__ id; struct ucl_emitter_functions* func; } ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 scalar_t__ UCL_EMIT_CONFIG ; 
 scalar_t__ UCL_EMIT_YAML ; 
 scalar_t__ UCL_OBJECT ; 
 int UCL_OBJECT_NEED_KEY_ESCAPE ; 
 int /*<<< orphan*/  stub1 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_elt_string_write_json (char*,int,struct ucl_emitter_context*) ; 

__attribute__((used)) static void
ucl_emitter_print_key (bool print_key, struct ucl_emitter_context *ctx,
		const ucl_object_t *obj, bool compact)
{
	const struct ucl_emitter_functions *func = ctx->func;

	if (!print_key) {
		return;
	}

	if (ctx->id == UCL_EMIT_CONFIG) {
		if (obj->flags & UCL_OBJECT_NEED_KEY_ESCAPE) {
			ucl_elt_string_write_json (obj->key, obj->keylen, ctx);
		}
		else {
			func->ucl_emitter_append_len (obj->key, obj->keylen, func->ud);
		}

		if (obj->type != UCL_OBJECT && obj->type != UCL_ARRAY) {
			func->ucl_emitter_append_len (" = ", 3, func->ud);
		}
		else {
			func->ucl_emitter_append_character (' ', 1, func->ud);
		}
	}
	else if (ctx->id == UCL_EMIT_YAML) {
		if (obj->keylen > 0 && (obj->flags & UCL_OBJECT_NEED_KEY_ESCAPE)) {
			ucl_elt_string_write_json (obj->key, obj->keylen, ctx);
		}
		else if (obj->keylen > 0) {
			func->ucl_emitter_append_len (obj->key, obj->keylen, func->ud);
		}
		else {
			func->ucl_emitter_append_len ("null", 4, func->ud);
		}

		func->ucl_emitter_append_len (": ", 2, func->ud);
	}
	else {
		if (obj->keylen > 0) {
			ucl_elt_string_write_json (obj->key, obj->keylen, ctx);
		}
		else {
			func->ucl_emitter_append_len ("null", 4, func->ud);
		}

		if (compact) {
			func->ucl_emitter_append_character (':', 1, func->ud);
		}
		else {
			func->ucl_emitter_append_len (": ", 2, func->ud);
		}
	}
}