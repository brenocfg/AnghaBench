#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ query_node_t ;

/* Variables and functions */
 TYPE_1__* new_query_node (int /*<<< orphan*/ ) ; 
 char* parse_ptr ; 
 void* parse_query_term () ; 
 int /*<<< orphan*/  qn_and ; 
 int /*<<< orphan*/  qn_minus ; 
 int /*<<< orphan*/  qn_or ; 
 int /*<<< orphan*/  skipspc () ; 

__attribute__((used)) static query_node_t *parse_query_expr (void) {
  query_node_t *X, *Y;
  X = parse_query_term ();
  if (!X) {
    return 0;
  }
  while (1) {
    skipspc();
    if (*parse_ptr != '&' && *parse_ptr != '+' && *parse_ptr != '-' && *parse_ptr != '#') {
      return X;
    }
    Y = new_query_node (*parse_ptr == '#' ? qn_or : (*parse_ptr == '-' ? qn_minus : qn_and));
    if (!Y) {
      return 0;
    }
    Y->left = X;
    parse_ptr++;
    Y->right = parse_query_term ();
    if (!Y->right) {
      return 0;
    }
    X = Y;
  }
  return X;
}