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
 int /*<<< orphan*/  parse_partial_comb_app_decl ; 
 int /*<<< orphan*/  parse_partial_type_app_decl ; 
 int /*<<< orphan*/  type_partial_app_decl ; 

struct tree *parse_partial_app_decl (void) {
  PARSE_INIT (type_partial_app_decl);
  PARSE_TRY_OPT (parse_partial_type_app_decl);
  PARSE_TRY_OPT (parse_partial_comb_app_decl);
  PARSE_FAIL;
}