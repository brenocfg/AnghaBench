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
struct TYPE_4__ {int /*<<< orphan*/  freq; struct TYPE_4__* next; } ;
typedef  TYPE_1__ word_t ;
struct TYPE_5__ {TYPE_1__** A; } ;
typedef  TYPE_2__ word_hash_t ;

/* Variables and functions */
 int PRIME ; 

long import_freq (long long *table, const word_hash_t *Set) {
  long cnt = 0;
  int i;
  const word_t *ptr;
  for (i = 0; i < PRIME; i++) {
    for (ptr = Set->A[i]; ptr; ptr = ptr->next) {
      if (ptr->freq > 0) {
	*table++ = ptr->freq;
	cnt++;
      }
    }
  }
  return cnt;
}