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
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ lex; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT (char*) ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OK ; 
 int /*<<< orphan*/  PARSE_TRY_PES (int /*<<< orphan*/ ) ; 
 scalar_t__ lex_eof ; 
 scalar_t__ lex_triple_minus ; 
 TYPE_2__ parse ; 
 int /*<<< orphan*/  parse_declaration ; 
 int /*<<< orphan*/  type_constr_declarations ; 

struct tree *parse_constr_declarations (void) {
  PARSE_INIT (type_constr_declarations);
  if (parse.lex.type == lex_triple_minus || parse.lex.type == lex_eof) { PARSE_OK; }
  while (1) {
    PARSE_TRY_PES (parse_declaration);
    EXPECT (";");
    if (parse.lex.type == lex_eof || parse.lex.type == lex_triple_minus) { PARSE_OK; }
  }
}