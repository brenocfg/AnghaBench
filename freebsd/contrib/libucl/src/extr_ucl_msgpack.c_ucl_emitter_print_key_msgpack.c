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
struct TYPE_3__ {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ ucl_object_t ;
struct ucl_emitter_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ucl_emitter_print_string_msgpack (struct ucl_emitter_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ucl_emitter_print_key_msgpack (bool print_key, struct ucl_emitter_context *ctx,
		const ucl_object_t *obj)
{
	if (print_key) {
		ucl_emitter_print_string_msgpack (ctx, obj->key, obj->keylen);
	}
}