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
struct tree {scalar_t__ type; int nc; int /*<<< orphan*/ * c; } ;
struct tl_combinator_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct tl_combinator_tree* tl_parse_nat_term (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ type_multiplicity ; 

struct tl_combinator_tree *tl_parse_multiplicity (struct tree *T) {
  assert (T->type == type_multiplicity);
  assert (T->nc == 1);
  return tl_parse_nat_term (T->c[0], 0);
}