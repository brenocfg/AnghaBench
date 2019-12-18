#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int words; TYPE_1__** E; } ;
typedef  TYPE_2__ searchy_iheap_phrase_t ;
typedef  int /*<<< orphan*/  pos ;
typedef  int /*<<< orphan*/  o ;
struct TYPE_4__ {int* positions; } ;

/* Variables and functions */
 int INT_MAX ; 
 void* alloca (int) ; 
 int /*<<< orphan*/  assert (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int phrase_count_extra_words (searchy_iheap_phrase_t *P) {
  const int terms = P->words;
  //fprintf (stderr, "%s: terms = %d\n", __func__, terms);
  int i, *o = alloca (sizeof (o[0]) * terms), **pos = alloca (sizeof (pos[0]) * terms);
  for (i = 0; i < terms; i++) {
    pos[i] = P->E[i]->positions;
    assert (pos[i]);
    (pos[i])++;
  }
  memset (o, 0, sizeof (o[0]) * terms);
/*
  if (verbosity >= 3) {
    for (i = 0; i < Q_terms; i++) {
      int j;
      fprintf (stderr, "[");
      for (j = 0; j < pos[i][-1]; j++) {
        fprintf (stderr, " %d", pos[i][j]);
      }
      fprintf (stderr, " ]\n");
    }
  }
*/
  int r = INT_MAX;
  for (i = 0; i < pos[0][-1]; i++) {
    int cur = pos[0][i], j;
    for (j = 1; j < terms; j++) {
      int num = pos[j][-1];
      while (o[j] < num && pos[j][o[j]] <= cur) {
        o[j]++;
      }
      if (o[j] >= num) {
        return r - terms;
      }
      cur = pos[j][o[j]];
    }
    const int l = cur - pos[0][i] + 1;
    if (r > l) {
      //fprintf (stderr, "%s: l = %d, terms = %d\n", __func__, l, terms);
      r = l;
    }
  }
  return r - terms;
}