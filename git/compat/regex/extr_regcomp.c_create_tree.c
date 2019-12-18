#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  re_token_type_t ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ re_token_t ;
typedef  int /*<<< orphan*/  re_dfa_t ;
typedef  int /*<<< orphan*/  bin_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/ * create_token_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bin_tree_t *
create_tree (re_dfa_t *dfa, bin_tree_t *left, bin_tree_t *right,
	     re_token_type_t type)
{
  re_token_t t;
  t.type = type;
  return create_token_tree (dfa, left, right, &t);
}