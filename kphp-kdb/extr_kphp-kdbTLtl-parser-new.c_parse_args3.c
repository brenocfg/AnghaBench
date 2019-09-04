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
struct tree {int dummy; } ;
struct parse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPECT (char*) ; 
 scalar_t__ LEX_CHAR (char) ; 
 int /*<<< orphan*/  PARSE_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OK ; 
 int /*<<< orphan*/  PARSE_TRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_TRY_PES (int /*<<< orphan*/ ) ; 
 scalar_t__ S ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  load_parse (struct parse) ; 
 int /*<<< orphan*/  parse_optional_arg_def ; 
 int /*<<< orphan*/  parse_type_term ; 
 int /*<<< orphan*/  parse_var_ident_opt ; 
 struct parse save_parse () ; 
 int /*<<< orphan*/  tree_add_child (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  type_args3 ; 
 int /*<<< orphan*/  type_exclam ; 

struct tree *parse_args3 (void) {
  PARSE_INIT (type_args3);
  PARSE_TRY_PES (parse_var_ident_opt);
  EXPECT (":");
  struct parse so = save_parse ();
  PARSE_TRY (parse_optional_arg_def);
  if (S) {
    tree_add_child (T, S);
  } else {
    load_parse (so);    
  }
  if (LEX_CHAR ('!')) {
    PARSE_ADD (type_exclam);
    EXPECT ("!");
  }
  PARSE_TRY_PES (parse_type_term);
  PARSE_OK;
}