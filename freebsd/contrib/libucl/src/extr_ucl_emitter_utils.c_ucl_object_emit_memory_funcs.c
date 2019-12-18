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
struct ucl_emitter_functions {TYPE_1__* ud; int /*<<< orphan*/  ucl_emitter_free_func; int /*<<< orphan*/  ucl_emitter_append_len; int /*<<< orphan*/  ucl_emitter_append_int; int /*<<< orphan*/  ucl_emitter_append_double; int /*<<< orphan*/  ucl_emitter_append_character; } ;
struct TYPE_3__ {void** pd; void* d; } ;
typedef  TYPE_1__ UT_string ;

/* Variables and functions */
 struct ucl_emitter_functions* calloc (int,int) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  ucl_utstring_append_character ; 
 int /*<<< orphan*/  ucl_utstring_append_double ; 
 int /*<<< orphan*/  ucl_utstring_append_int ; 
 int /*<<< orphan*/  ucl_utstring_append_len ; 
 int /*<<< orphan*/  utstring_new (TYPE_1__*) ; 

struct ucl_emitter_functions*
ucl_object_emit_memory_funcs (void **pmem)
{
	struct ucl_emitter_functions *f;
	UT_string *s;

	f = calloc (1, sizeof (*f));

	if (f != NULL) {
		f->ucl_emitter_append_character = ucl_utstring_append_character;
		f->ucl_emitter_append_double = ucl_utstring_append_double;
		f->ucl_emitter_append_int = ucl_utstring_append_int;
		f->ucl_emitter_append_len = ucl_utstring_append_len;
		f->ucl_emitter_free_func = free;
		utstring_new (s);
		f->ud = s;
		*pmem = s->d;
		s->pd = pmem;
	}

	return f;
}