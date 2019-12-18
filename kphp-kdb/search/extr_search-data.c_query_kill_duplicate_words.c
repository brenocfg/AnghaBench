#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct query_nodes_list {TYPE_1__* v; struct query_nodes_list* next; } ;
struct TYPE_8__ {scalar_t__ op; scalar_t__ word; struct TYPE_8__* right; struct TYPE_8__* left; int /*<<< orphan*/  frequency; struct query_nodes_list* head; } ;
typedef  TYPE_1__ query_node_t ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 scalar_t__ MAX_QUERY_NODES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmp_query_node ; 
 int /*<<< orphan*/  get_word_frequency (scalar_t__) ; 
 int qn_and ; 
 scalar_t__ qn_cum_and ; 
 scalar_t__ qn_cum_or ; 
 int qn_or ; 
 scalar_t__ qn_word ; 
 int /*<<< orphan*/  qsort (TYPE_1__**,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* query_nodes_kill_dup_buffer ; 
 scalar_t__ tot_query_nodes_kill_dup ; 
 int /*<<< orphan*/  zzfree (TYPE_1__**,int) ; 
 TYPE_1__** zzmalloc (int) ; 

__attribute__((used)) static query_node_t *query_kill_duplicate_words (query_node_t *X) {
  if (!X) { return 0; }
  if (X->op == qn_cum_and || X->op == qn_cum_or) {
    int op = (X->op == qn_cum_and) ? qn_and : qn_or;
    struct query_nodes_list *p;
    int i, k = 0;
    for (p = X->head; p != 0; p = p->next) {
      p->v = query_kill_duplicate_words (p->v);
      k++;
    }
    query_node_t **a = zzmalloc (sizeof (query_node_t *) * k);
    k = 0;
    for (p = X->head; p != 0; p = p->next) {
      a[k++] = p->v;
    }
    for (i = 0; i < k; i++) {
      if (a[i]->op == qn_word) {
        a[i]->frequency = get_word_frequency (a[i]->word);
      }
    }
    qsort (a, k, sizeof (a[0]), cmp_query_node);
    int m = 0;
    /* remove duplicate words */
    for (i = 1; i < k; i++) {
      if (a[i]->op != qn_word || a[i]->word != a[m]->word) {
        a[++m] = a[i];
      }
    }
    query_node_t *w = a[0];
    for (i = 1; i <= m; i++) {
      assert (tot_query_nodes_kill_dup < MAX_QUERY_NODES);
      query_node_t *t = &query_nodes_kill_dup_buffer[tot_query_nodes_kill_dup++];
      t->op = op;
      t->left = w;
      t->right = a[i];
      w = t;
    }
    zzfree (a, sizeof (query_node_t *) * k);
    return w;
  } else {
    X->left = query_kill_duplicate_words (X->left);
    X->right = query_kill_duplicate_words (X->right);
    return X;
  }
}