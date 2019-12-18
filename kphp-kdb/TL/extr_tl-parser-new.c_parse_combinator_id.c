#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tree {int dummy; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  text; } ;
struct TYPE_4__ {scalar_t__ type; int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  ptr; } ;
struct TYPE_5__ {TYPE_1__ lex; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_FAIL ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OK ; 
 TYPE_3__* T ; 
 scalar_t__ lex_lc_ident ; 
 TYPE_2__ parse ; 
 int /*<<< orphan*/  parse_error (char*) ; 
 int /*<<< orphan*/  parse_lex () ; 
 int /*<<< orphan*/  type_combinator_id ; 

struct tree *parse_combinator_id (void) {
  PARSE_INIT (type_combinator_id);
  if (parse.lex.type == lex_lc_ident && !(parse.lex.flags & 2)) {
    T->text = parse.lex.ptr;
    T->len = parse.lex.len;
    T->flags = parse.lex.flags;
    parse_lex ();
    PARSE_OK;
  } else {
    parse_error ("Can not parse combinator id");
    PARSE_FAIL;
  } 
}