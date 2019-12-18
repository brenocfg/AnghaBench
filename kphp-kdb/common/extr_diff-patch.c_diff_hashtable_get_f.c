#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int offset; int length; } ;
typedef  TYPE_2__ diff_string_t ;
struct TYPE_8__ {unsigned int size; int a; int* next; int* e; TYPE_1__* H; } ;
typedef  TYPE_3__ diff_hashtable_t ;
struct TYPE_6__ {scalar_t__ length; int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int,unsigned char const*,int) ; 

__attribute__((used)) static int diff_hashtable_get_f (diff_hashtable_t *T, const unsigned char *const a, const diff_string_t *const S, int id) {
  unsigned hc1 = 0, hc2 = 0;
  int i;
  const unsigned char *b = a + S->offset;
  for (i = 0; i < S->length; i++) {
    hc1 = (239 * hc1) + (*b);
    hc2 = (3 * hc2) + (*b);
    b++;
  }
  hc1 %= T->size;
  hc2 = 1 + (hc2 % (T->size - 1));
  b = a + S->offset;
  while (T->H[hc1].length >= 0) {
    if (T->H[hc1].length == S->length && !memcmp (T->a + T->H[hc1].offset, b, S->length)) {
      if (id >= 0) {
        T->next[id] = T->e[hc1];
        T->e[hc1]= id;
      }
      return T->e[hc1];
    }
    if ( (hc1 += hc2) >= T->size) {
      hc1 -= T->size;
    }
  }
  if (id < 0) {
    return -1;
  }
  T->H[hc1].offset = S->offset;
  T->H[hc1].length = S->length;
  T->next[id] = T->e[hc1];
  T->e[hc1]= id;
  return T->e[hc1];
}