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
 int /*<<< orphan*/  parse_final_empty ; 
 int /*<<< orphan*/  parse_final_final ; 
 int /*<<< orphan*/  parse_final_new ; 
 int /*<<< orphan*/  type_final_decl ; 

struct tree *parse_final_decl (void) {
  PARSE_INIT (type_final_decl);
  PARSE_TRY_OPT (parse_final_new);
  PARSE_TRY_OPT (parse_final_final);
  PARSE_TRY_OPT (parse_final_empty);
  PARSE_FAIL;
}