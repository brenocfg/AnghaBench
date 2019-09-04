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

/* Variables and functions */
 int /*<<< orphan*/  PARSE_FAIL ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_TRY_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_builtin_combinator_decl ; 
 int /*<<< orphan*/  parse_combinator_decl ; 
 int /*<<< orphan*/  parse_final_decl ; 
 int /*<<< orphan*/  parse_partial_app_decl ; 
 int /*<<< orphan*/  type_declaration ; 

struct tree *parse_declaration (void) {
  PARSE_INIT (type_declaration);
  PARSE_TRY_OPT (parse_combinator_decl);
  PARSE_TRY_OPT (parse_partial_app_decl);
  PARSE_TRY_OPT (parse_final_decl);
  PARSE_TRY_OPT (parse_builtin_combinator_decl);
  PARSE_FAIL;
}