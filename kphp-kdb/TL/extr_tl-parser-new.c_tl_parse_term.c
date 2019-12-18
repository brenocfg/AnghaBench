#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tree {scalar_t__ type; int nc; TYPE_1__** c; } ;
struct tl_combinator_tree {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 struct tl_combinator_tree* L ; 
 int /*<<< orphan*/  TL_INIT (struct tl_combinator_tree*) ; 
 int /*<<< orphan*/  TL_TRY (int /*<<< orphan*/ ,struct tl_combinator_tree*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tl_parse_any_term (TYPE_1__*,int) ; 
 scalar_t__ type_percent ; 
 scalar_t__ type_term ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

struct tl_combinator_tree *tl_parse_term (struct tree *T, int s) {
  vkprintf (2, "tl_parse_term: s = %d\n", s);
  assert (T->type == type_term);
  int i = 0;
  while (i < T->nc && T->c[i]->type == type_percent) { i ++; s ++; } 
  assert (i < T->nc);
  TL_INIT (L);
  while (i < T->nc) {
    TL_TRY (tl_parse_any_term (T->c[i], s), L);
    s = 0;
    i ++;
  }
  return L;
}