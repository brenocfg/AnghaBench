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
typedef  int /*<<< orphan*/  type_desc ;
struct TYPE_3__ {char* s; int /*<<< orphan*/ * root; int /*<<< orphan*/ * token_list; } ;
typedef  TYPE_1__ expression ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (char*,char*) ; 
 int /*<<< orphan*/ * _cur_type ; 
 int /*<<< orphan*/  del_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_token_list (int /*<<< orphan*/ *) ; 
 int expression_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_token_list (char*) ; 
 int simplify_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sp_init () ; 

char *expression_compile (expression *e, char *s, type_desc *cur_type) {
  sp_init();
  _cur_type = cur_type;

  e->s = s;
  e->token_list = get_token_list (s);

  if (e->token_list == NULL) {
    FAIL ("can't split query [%s] into tokens", s);
  }

  e->root = gen_tree (e->token_list);
  if (e->root == NULL) {
    del_token_list (e->token_list);
    FAIL ("can't parse query [%s] as arithmetic expression", s);
  }

  int res = simplify_tree (e->root);
  if (!res) {
    del_token_list (e->token_list);
    del_node (e->root);
    FAIL ("can't parse query [%s] as arithmetic expression", s);
  }

  res = expression_prepare (e->root);
  if (!res) {
    del_token_list (e->token_list);
    del_node (e->root);
    FAIL ("can't prepare expression [%s]", s);
  }

  return NULL;
}