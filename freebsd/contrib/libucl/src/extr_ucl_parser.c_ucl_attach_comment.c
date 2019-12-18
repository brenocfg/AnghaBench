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
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_parser {TYPE_1__* last_comment; int /*<<< orphan*/  comments; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_OBJECT_INHERITED ; 
 int /*<<< orphan*/  ucl_object_insert_key (int /*<<< orphan*/ ,TYPE_1__*,char const*,int,int) ; 

__attribute__((used)) static void
ucl_attach_comment (struct ucl_parser *parser, ucl_object_t *obj, bool before)
{
	if (parser->last_comment) {
		ucl_object_insert_key (parser->comments, parser->last_comment,
				(const char *)&obj, sizeof (void *), true);

		if (before) {
			parser->last_comment->flags |= UCL_OBJECT_INHERITED;
		}

		parser->last_comment = NULL;
	}
}