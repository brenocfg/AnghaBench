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
typedef  int /*<<< orphan*/ * ucl_context_macro_handler ;
struct ucl_parser {int /*<<< orphan*/  macroes; } ;
struct TYPE_2__ {int /*<<< orphan*/ * context_handler; } ;
struct ucl_macro {int is_context; int /*<<< orphan*/  name; void* ud; TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ADD_KEYPTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucl_macro*) ; 
 struct ucl_macro* UCL_ALLOC (int) ; 
 int /*<<< orphan*/  hh ; 
 int /*<<< orphan*/  memset (struct ucl_macro*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void
ucl_parser_register_context_macro (struct ucl_parser *parser, const char *macro,
		ucl_context_macro_handler handler, void* ud)
{
	struct ucl_macro *new;

	if (macro == NULL || handler == NULL) {
		return;
	}

	new = UCL_ALLOC (sizeof (struct ucl_macro));
	if (new == NULL) {
		return;
	}

	memset (new, 0, sizeof (struct ucl_macro));
	new->h.context_handler = handler;
	new->name = strdup (macro);
	new->ud = ud;
	new->is_context = true;
	HASH_ADD_KEYPTR (hh, parser->macroes, new->name, strlen (new->name), new);
}