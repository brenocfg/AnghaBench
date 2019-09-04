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
struct TYPE_4__ {int type; scalar_t__ day; int owner; int place; int user_id; int item; } ;
typedef  TYPE_1__ item_t ;

/* Variables and functions */
 unsigned int HASH_SIZE ; 
 scalar_t__* HD ; 
 TYPE_1__** HX ; 
 scalar_t__ Hs ; 
 scalar_t__ Ht ; 
 int MAX_HASH_ITERATIONS ; 
 int* TypeFlags ; 
 int* TypeReduce ; 
 int /*<<< orphan*/  assert (int) ; 

int ihash_lookup (item_t *A, int mode) {
  int t = A->type, tt = mode ? t : TypeReduce[t];
  item_t *B;
  unsigned h = tt * 17239;
  unsigned h2 = tt;

  if (A->day + Hs > Ht) {
    Ht = A->day + Hs;
  }

  if (mode) {
    if (TypeFlags[t] & 1) {
      h += 17 * A->owner;
      h2 += 239 * A->owner;
      mode |= 8;
    }
    if (TypeFlags[t] & 2) {
      h += 239 * A->place;
      h2 += 17 * A->place;
      mode |= 16;
    }
    if (TypeFlags[t] & 4) {
      h += A->user_id * 239;
      h2 += A->user_id * 10000;
      mode |= 2;
    }
    if (TypeFlags[t] & 8) {
      h += 666 * A->item;
      h2 += 13 * A->item;
      mode |= 4;
    }
  } else {
    h += A->user_id * 239;
    h2 += A->user_id * 10000;
    mode |= 2;

    if (mode & 32) {
      h += 666 * A->item;
      h2 += 13 * A->item;
      mode |= 4;
    }
  }

  h %= HASH_SIZE;
  h2 = (h2 % (HASH_SIZE - 1)) + 1;

  int hash_iterations = 0;

  while (1) {
    if (HD[h] != Ht || !HX[h]) {
      break;
    }
    B = HX[h];
    if (B->type == A->type || (!(mode & 1) && TypeReduce[B->type] == tt)) {
      if (!(mode & 2) || (A->user_id == B->user_id)) {
        if (!(mode & 4) || (A->item == B->item)) {
          if (!(mode & 8) || (A->owner == B->owner)) {
            if (!(mode & 16) || (A->place == B->place)) {
              return h;
            }
          }
        }
      }
    }
    h += h2;
    if (h >= HASH_SIZE) {
      h -= HASH_SIZE;
    }
    assert (++hash_iterations <= MAX_HASH_ITERATIONS);
  }

  HD[h] = Ht;
  HX[h] = 0;
  return h;
}