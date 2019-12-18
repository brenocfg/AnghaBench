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
 scalar_t__ LEX_CHAR (char) ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OK ; 
 int /*<<< orphan*/  PARSE_TRY_PES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_boxed_type_ident ; 
 int /*<<< orphan*/  parse_expr ; 
 int /*<<< orphan*/  parse_subexpr ; 
 int /*<<< orphan*/  type_result_type ; 

struct tree *parse_result_type (void) {
  PARSE_INIT (type_result_type);
  PARSE_TRY_PES (parse_boxed_type_ident);
  if (LEX_CHAR ('<')) {
    EXPECT ("<");
    while (1) {
      PARSE_TRY_PES (parse_expr);
      if (LEX_CHAR ('>')) { break; }
      EXPECT (",");
    }
    EXPECT (">");
    PARSE_OK;
  } else {
    while (1) {
      if (LEX_CHAR (';')) { PARSE_OK; }
      PARSE_TRY_PES (parse_subexpr);
    }
  }
}