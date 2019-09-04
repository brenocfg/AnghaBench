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
struct TYPE_3__ {int doc_id; int position; int /*<<< orphan*/  word; } ;
typedef  TYPE_1__ pair_t ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 TYPE_1__* P ; 
 scalar_t__ PC ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ max_pairs ; 
 int /*<<< orphan*/  stderr ; 

void keep_pair (int doc_id, hash_t word, int position) {
  if (PC >= max_pairs) {
    fprintf (stderr, "\nThere are too many pairs (max_pairs = %d).\n"
                     "Try increase max_pairs using -P command line switch.\n", max_pairs);
    exit (1);
  }
  pair_t *P1 = &P[PC++];
  P1->word = word;
  P1->doc_id = doc_id;
  P1->position = position;
}