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
struct ucl_parser {int flags; int /*<<< orphan*/  comments; int /*<<< orphan*/ * includepaths; } ;

/* Variables and functions */
 struct ucl_parser* UCL_ALLOC (int) ; 
 int /*<<< orphan*/  UCL_OBJECT ; 
 int UCL_PARSER_NO_FILEVARS ; 
 int UCL_PARSER_SAVE_COMMENTS ; 
 int /*<<< orphan*/  memset (struct ucl_parser*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ucl_include_handler ; 
 int /*<<< orphan*/  ucl_includes_handler ; 
 int /*<<< orphan*/  ucl_inherit_handler ; 
 int /*<<< orphan*/  ucl_load_handler ; 
 int /*<<< orphan*/  ucl_object_typed_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_parser_register_context_macro (struct ucl_parser*,char*,int /*<<< orphan*/ ,struct ucl_parser*) ; 
 int /*<<< orphan*/  ucl_parser_register_macro (struct ucl_parser*,char*,int /*<<< orphan*/ ,struct ucl_parser*) ; 
 int /*<<< orphan*/  ucl_parser_set_filevars (struct ucl_parser*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ucl_priority_handler ; 
 int /*<<< orphan*/  ucl_try_include_handler ; 

struct ucl_parser*
ucl_parser_new (int flags)
{
	struct ucl_parser *parser;

	parser = UCL_ALLOC (sizeof (struct ucl_parser));
	if (parser == NULL) {
		return NULL;
	}

	memset (parser, 0, sizeof (struct ucl_parser));

	ucl_parser_register_macro (parser, "include", ucl_include_handler, parser);
	ucl_parser_register_macro (parser, "try_include", ucl_try_include_handler, parser);
	ucl_parser_register_macro (parser, "includes", ucl_includes_handler, parser);
	ucl_parser_register_macro (parser, "priority", ucl_priority_handler, parser);
	ucl_parser_register_macro (parser, "load", ucl_load_handler, parser);
	ucl_parser_register_context_macro (parser, "inherit", ucl_inherit_handler, parser);

	parser->flags = flags;
	parser->includepaths = NULL;

	if (flags & UCL_PARSER_SAVE_COMMENTS) {
		parser->comments = ucl_object_typed_new (UCL_OBJECT);
	}

	if (!(flags & UCL_PARSER_NO_FILEVARS)) {
		/* Initial assumption about filevars */
		ucl_parser_set_filevars (parser, NULL, false);
	}

	return parser;
}