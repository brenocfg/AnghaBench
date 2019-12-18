#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree {int dummy; } ;
struct parse {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ lex; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct parse*) ; 
 scalar_t__ lex_error ; 
 scalar_t__ lex_none ; 
 int /*<<< orphan*/  load_parse (struct parse) ; 
 TYPE_2__ parse ; 
 int /*<<< orphan*/  parse_lex () ; 
 struct tree* parse_program () ; 

struct tree *tl_parse_lex (struct parse *_parse) {
  assert (_parse);
  load_parse (*_parse);
  if (parse.lex.type == lex_none) {
    parse_lex ();
  }
  if (parse.lex.type == lex_error) {
    return 0;
  }
  return parse_program ();
}