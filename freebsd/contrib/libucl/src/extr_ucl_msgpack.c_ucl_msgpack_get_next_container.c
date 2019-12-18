#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct ucl_stack {int level; TYPE_1__* obj; struct ucl_stack* next; } ;
struct ucl_parser {TYPE_1__* cur_obj; struct ucl_stack* stack; } ;
struct TYPE_2__ {scalar_t__ type; scalar_t__ len; } ;

/* Variables and functions */
 int MSGPACK_CONTAINER_BIT ; 
 scalar_t__ UCL_OBJECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct ucl_stack*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static struct ucl_stack *
ucl_msgpack_get_next_container (struct ucl_parser *parser)
{
	struct ucl_stack *cur = NULL;
	uint64_t level;

	cur = parser->stack;

	if (cur == NULL) {
		return NULL;
	}

	if (cur->level & MSGPACK_CONTAINER_BIT) {
		level = cur->level & ~MSGPACK_CONTAINER_BIT;

		if (level == 0) {
			/* We need to switch to the previous container */
			parser->stack = cur->next;
			parser->cur_obj = cur->obj;
			free (cur);

#ifdef MSGPACK_DEBUG_PARSER
			cur = parser->stack;
			while (cur) {
				fprintf(stderr, "-");
				cur = cur->next;
			}
			fprintf(stderr, "-%s -> %d\n", parser->cur_obj->type == UCL_OBJECT ? "object" : "array", (int)parser->cur_obj->len);
#endif

			return ucl_msgpack_get_next_container (parser);
		}
	}

	/*
	 * For UCL containers we don't know length, so we just insert the whole
	 * message pack blob into the top level container
	 */

	assert (cur->obj != NULL);

	return cur;
}