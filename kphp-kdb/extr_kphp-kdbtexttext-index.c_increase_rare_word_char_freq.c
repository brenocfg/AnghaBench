#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long long freq; size_t len; struct TYPE_5__* next; scalar_t__* str; } ;
typedef  TYPE_1__ word_t ;
struct TYPE_6__ {TYPE_1__** A; } ;
typedef  TYPE_2__ word_hash_t ;

/* Variables and functions */
 int PRIME ; 
 int /*<<< orphan*/  zfree (TYPE_1__*,int) ; 

int increase_rare_word_char_freq (long long Freq[], long long LenFreq[], word_hash_t *Set, int max_freq) {
  int i, j, cnt = 0;
  long long f;
  word_t *ptr, **pptr;
  for (i = 0; i < PRIME; i++) {
    for (pptr = &Set->A[i], ptr = *pptr; ptr; ptr = *pptr) {
      f = ptr->freq;
      if (f <= max_freq && f > 0) {
	*pptr = ptr->next;
	ptr->freq = -f;
	cnt++;
	LenFreq[ptr->len] += f;
	for (j = 0; j < ptr->len; j++) {
	  Freq[(unsigned char) ptr->str[j]] += f;
	}
	zfree (ptr, sizeof (word_t) + ptr->len);
      } else {
	pptr = &ptr->next;
      }
    }
  }
  return cnt;
}