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
struct ucl_emitter_functions {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* ucl_emitter_append_character ) (char,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ucl_emitter_append_len ) (char const*,size_t,int /*<<< orphan*/ ) ;} ;
struct ucl_emitter_context {struct ucl_emitter_functions* func; } ;

/* Variables and functions */
 int UCL_CHARACTER_DENIED ; 
 int UCL_CHARACTER_JSON_UNSAFE ; 
 int /*<<< orphan*/  stub1 (char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (char,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ucl_test_character (char const,int) ; 

void
ucl_elt_string_write_json (const char *str, size_t size,
		struct ucl_emitter_context *ctx)
{
	const char *p = str, *c = str;
	size_t len = 0;
	const struct ucl_emitter_functions *func = ctx->func;

	func->ucl_emitter_append_character ('"', 1, func->ud);

	while (size) {
		if (ucl_test_character (*p, UCL_CHARACTER_JSON_UNSAFE|UCL_CHARACTER_DENIED)) {
			if (len > 0) {
				func->ucl_emitter_append_len (c, len, func->ud);
			}
			switch (*p) {
			case '\n':
				func->ucl_emitter_append_len ("\\n", 2, func->ud);
				break;
			case '\r':
				func->ucl_emitter_append_len ("\\r", 2, func->ud);
				break;
			case '\b':
				func->ucl_emitter_append_len ("\\b", 2, func->ud);
				break;
			case '\t':
				func->ucl_emitter_append_len ("\\t", 2, func->ud);
				break;
			case '\f':
				func->ucl_emitter_append_len ("\\f", 2, func->ud);
				break;
			case '\\':
				func->ucl_emitter_append_len ("\\\\", 2, func->ud);
				break;
			case '"':
				func->ucl_emitter_append_len ("\\\"", 2, func->ud);
				break;
			default:
				/* Emit unicode unknown character */
				func->ucl_emitter_append_len ("\\uFFFD", 5, func->ud);
				break;
			}
			len = 0;
			c = ++p;
		}
		else {
			p ++;
			len ++;
		}
		size --;
	}

	if (len > 0) {
		func->ucl_emitter_append_len (c, len, func->ud);
	}

	func->ucl_emitter_append_character ('"', 1, func->ud);
}