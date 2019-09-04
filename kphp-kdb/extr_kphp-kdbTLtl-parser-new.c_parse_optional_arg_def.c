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
 int /*<<< orphan*/  EXPECT (char*) ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OK ; 
 int /*<<< orphan*/  PARSE_TRY_PES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_nat_const ; 
 int /*<<< orphan*/  parse_var_ident ; 
 int /*<<< orphan*/  type_optional_arg_def ; 

struct tree *parse_optional_arg_def (void) {
  PARSE_INIT (type_optional_arg_def);
  PARSE_TRY_PES (parse_var_ident);
  EXPECT (".");
  PARSE_TRY_PES (parse_nat_const);
  EXPECT ("?");
  PARSE_OK;
}