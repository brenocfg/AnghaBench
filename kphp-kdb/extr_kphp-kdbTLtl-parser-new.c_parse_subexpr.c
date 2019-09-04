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
 int /*<<< orphan*/  LEX_CHAR (char) ; 
 int /*<<< orphan*/  PARSE_FAIL ; 
 int /*<<< orphan*/  PARSE_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OK ; 
 int /*<<< orphan*/  PARSE_TRY (int /*<<< orphan*/ ) ; 
 scalar_t__ S ; 
 int /*<<< orphan*/  T ; 
 int /*<<< orphan*/  parse_nat_const ; 
 int /*<<< orphan*/  parse_term ; 
 int /*<<< orphan*/  tree_add_child (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  type_subexpr ; 

struct tree *parse_subexpr (void) {
  PARSE_INIT (type_subexpr);
  int was_term = 0;
  int cc = 0;

  while (1) {
    PARSE_TRY (parse_nat_const);
    if (S) {
      tree_add_child (T, S);
    } else if (!was_term) {
      was_term = 1;
      PARSE_TRY (parse_term);
      if (S) {
        tree_add_child (T, S);       
      } else {
        break;
      }
    }
    cc ++;
    if (!LEX_CHAR ('+')) {
      break;
    }
    EXPECT ("+");
  }
  if (!cc) {
    PARSE_FAIL;
  } else {
    PARSE_OK;
  }
}