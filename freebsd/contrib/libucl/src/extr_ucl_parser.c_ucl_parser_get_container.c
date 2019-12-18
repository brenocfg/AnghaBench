#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ type; } ;
typedef  TYPE_3__ ucl_object_t ;
struct ucl_parser {TYPE_3__* cur_obj; TYPE_2__* stack; TYPE_1__* chunks; } ;
struct TYPE_11__ {TYPE_3__* obj; } ;
struct TYPE_10__ {int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 int /*<<< orphan*/  UCL_NULL ; 
 int /*<<< orphan*/  ucl_array_append (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ucl_attach_comment (struct ucl_parser*,TYPE_3__*,int) ; 
 TYPE_3__* ucl_object_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_object_unref (TYPE_3__*) ; 

__attribute__((used)) static inline ucl_object_t*
ucl_parser_get_container (struct ucl_parser *parser)
{
	ucl_object_t *t, *obj = NULL;

	if (parser == NULL || parser->stack == NULL || parser->stack->obj == NULL) {
		return NULL;
	}

	if (parser->stack->obj->type == UCL_ARRAY) {
		/* Object must be allocated */
		obj = ucl_object_new_full (UCL_NULL, parser->chunks->priority);
		t = parser->stack->obj;

		if (!ucl_array_append (t, obj)) {
			ucl_object_unref (obj);
			return NULL;
		}

		parser->cur_obj = obj;
		ucl_attach_comment (parser, obj, false);
	}
	else {
		/* Object has been already allocated */
		obj = parser->cur_obj;
	}

	return obj;
}