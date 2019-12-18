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
typedef  int uint64_t ;
struct ucl_stack {int level; struct ucl_stack* next; } ;
struct ucl_parser {struct ucl_stack* stack; int /*<<< orphan*/  err; } ;
struct ucl_msgpack_parser {int flags; } ;

/* Variables and functions */
 int MSGPACK_CONTAINER_BIT ; 
 int MSGPACK_FLAG_ASSOC ; 
 int MSGPACK_FLAG_CONTAINER ; 
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline struct ucl_stack *
ucl_msgpack_get_container (struct ucl_parser *parser,
		struct ucl_msgpack_parser *obj_parser, uint64_t len)
{
	struct ucl_stack *stack;

	assert (obj_parser != NULL);

	if (obj_parser->flags & MSGPACK_FLAG_CONTAINER) {
		assert ((len & MSGPACK_CONTAINER_BIT) == 0);
		/*
		 * Insert new container to the stack
		 */
		if (parser->stack == NULL) {
			parser->stack = calloc (1, sizeof (struct ucl_stack));

			if (parser->stack == NULL) {
				ucl_create_err (&parser->err, "no memory");
				return NULL;
			}
		}
		else {
			stack = calloc (1, sizeof (struct ucl_stack));

			if (stack == NULL) {
				ucl_create_err (&parser->err, "no memory");
				return NULL;
			}

			stack->next = parser->stack;
			parser->stack = stack;
		}

		parser->stack->level = len | MSGPACK_CONTAINER_BIT;

#ifdef MSGPACK_DEBUG_PARSER
		stack = parser->stack;
		while (stack) {
			fprintf(stderr, "+");
			stack = stack->next;
		}

		fprintf(stderr, "%s -> %d\n", obj_parser->flags & MSGPACK_FLAG_ASSOC ? "object" : "array", (int)len);
#endif
	}
	else {
		/*
		 * Get the current stack top
		 */
		if (parser->stack) {
			return parser->stack;
		}
		else {
			ucl_create_err (&parser->err, "bad top level object for msgpack");
			return NULL;
		}
	}

	return parser->stack;
}