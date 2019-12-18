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
 int /*<<< orphan*/  PARSE_FAIL ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OK ; 
 int /*<<< orphan*/  PARSE_TRY_PES (int /*<<< orphan*/ ) ; 
 scalar_t__ expect (char*) ; 
 scalar_t__ lex_eof ; 
 scalar_t__ lex_error ; 
 TYPE_2__ parse ; 
 int /*<<< orphan*/  parse_constr_declarations ; 
 int /*<<< orphan*/  parse_fun_declarations ; 
 int /*<<< orphan*/  type_tl_program ; 

struct tree *parse_program (void) {
  PARSE_INIT (type_tl_program);
  while (1) {
    PARSE_TRY_PES (parse_constr_declarations);
    if (parse.lex.type == lex_eof) { PARSE_OK; }
    if (parse.lex.type == lex_error || expect ("---") < 0 || expect ("functions") < 0 || expect ("---") < 0) { PARSE_FAIL; }

    PARSE_TRY_PES (parse_fun_declarations);
    if (parse.lex.type == lex_eof) { PARSE_OK; }
    if (parse.lex.type == lex_error || expect ("---") < 0 || expect ("types") < 0 || expect ("---") < 0) { PARSE_FAIL; }
  }
}