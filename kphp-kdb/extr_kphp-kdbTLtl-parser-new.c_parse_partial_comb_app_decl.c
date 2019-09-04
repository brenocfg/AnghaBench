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
 scalar_t__ LEX_CHAR (char) ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OK ; 
 int /*<<< orphan*/  PARSE_TRY_PES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_combinator_id ; 
 int /*<<< orphan*/  parse_subexpr ; 
 int /*<<< orphan*/  type_partial_comb_app_decl ; 

struct tree *parse_partial_comb_app_decl (void) {
  PARSE_INIT (type_partial_comb_app_decl);
  PARSE_TRY_PES (parse_combinator_id);
  while (1) {
    PARSE_TRY_PES (parse_subexpr);
    if (LEX_CHAR (';')) { break; }
  }
  PARSE_OK;
}