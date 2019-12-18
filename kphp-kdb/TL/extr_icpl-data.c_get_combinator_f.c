#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int name_length; int arity; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ icpl_combinator_t ;

/* Variables and functions */
 TYPE_1__** COMBINATORS ; 
 unsigned char COMBINATORS_PRIME ; 
 int /*<<< orphan*/  assert (int) ; 
 double combinators ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  zmalloc (int) ; 
 TYPE_1__* zmalloc0 (int) ; 

icpl_combinator_t *get_combinator_f (const char *name, int length, int force) {
  unsigned char h1 = 0, h2 = 0;
  int i;
  for (i = 0; i < length; i++) {
    h1 = 239 * h1 + name[i];
    h2 = 3 * h2 + name[i];
  }
  h1 %= COMBINATORS_PRIME;
  h2 = 1 + (h2 % (COMBINATORS_PRIME - 1));
  icpl_combinator_t *D;
  while ((D = COMBINATORS[h1])) {
    if (D->name_length == length && !memcmp (name, D->name, length)) {
      return D;
    }
    if ( (h1 += h2) >= COMBINATORS_PRIME) {
      h1 -= COMBINATORS_PRIME;
    }
  }
  if (!force) {
    return NULL;
  }
  combinators++;
  assert (combinators < (0.8 * COMBINATORS_PRIME));
  icpl_combinator_t *C = zmalloc0 (sizeof (*C));
  C->name = zmalloc (length);
  memcpy (C->name, name, length);
  C->name_length = length;
  C->arity = -1;
  return COMBINATORS[h1] = C;
}