#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * ov; } ;
struct TYPE_10__ {void* type; TYPE_1__ value; } ;
typedef  TYPE_3__ ucl_object_t ;
struct ucl_stack {int level; TYPE_3__* obj; } ;
struct ucl_parser {int flags; TYPE_3__* cur_obj; int /*<<< orphan*/  stack; int /*<<< orphan*/  err; int /*<<< orphan*/  state; TYPE_2__* chunks; } ;
struct TYPE_9__ {int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_PREPEND (int /*<<< orphan*/ ,struct ucl_stack*) ; 
 struct ucl_stack* UCL_ALLOC (int) ; 
 void* UCL_ARRAY ; 
 int /*<<< orphan*/  UCL_EINTERNAL ; 
 void* UCL_OBJECT ; 
 int UCL_PARSER_KEY_LOWERCASE ; 
 int /*<<< orphan*/  UCL_STATE_KEY ; 
 int /*<<< orphan*/  UCL_STATE_VALUE ; 
 int /*<<< orphan*/ * ucl_hash_create (int) ; 
 TYPE_3__* ucl_object_new_full (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_object_unref (TYPE_3__*) ; 
 int /*<<< orphan*/  ucl_set_err (struct ucl_parser*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline ucl_object_t *
ucl_parser_add_container (ucl_object_t *obj, struct ucl_parser *parser,
		bool is_array, int level)
{
	struct ucl_stack *st;

	if (!is_array) {
		if (obj == NULL) {
			obj = ucl_object_new_full (UCL_OBJECT, parser->chunks->priority);
		}
		else {
			obj->type = UCL_OBJECT;
		}
		if (obj->value.ov == NULL) {
			obj->value.ov = ucl_hash_create (parser->flags & UCL_PARSER_KEY_LOWERCASE);
		}
		parser->state = UCL_STATE_KEY;
	}
	else {
		if (obj == NULL) {
			obj = ucl_object_new_full (UCL_ARRAY, parser->chunks->priority);
		}
		else {
			obj->type = UCL_ARRAY;
		}
		parser->state = UCL_STATE_VALUE;
	}

	st = UCL_ALLOC (sizeof (struct ucl_stack));

	if (st == NULL) {
		ucl_set_err (parser, UCL_EINTERNAL, "cannot allocate memory for an object",
				&parser->err);
		ucl_object_unref (obj);
		return NULL;
	}

	st->obj = obj;
	st->level = level;
	LL_PREPEND (parser->stack, st);
	parser->cur_obj = obj;

	return obj;
}