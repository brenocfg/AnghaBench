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
struct TYPE_4__ {long long freq; int code_len; char* len; int /*<<< orphan*/  str; struct TYPE_4__* next; } ;
typedef  TYPE_1__ word_t ;
struct TYPE_5__ {TYPE_1__** A; } ;
typedef  TYPE_2__ word_hash_t ;

/* Variables and functions */
 int PRIME ; 
 int /*<<< orphan*/  dict_size ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,long long,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

long long export_codelen (long long *table, word_hash_t *Set) {
  int i;
  word_t *ptr;
  long long sum = 0;
  for (i = 0; i < PRIME; i++) {
    for (ptr = Set->A[i]; ptr; ptr = ptr->next) {
      if (ptr->freq > 0) {
	ptr->code_len = *table++;
	sum += (long long) ptr->code_len * ptr->freq;
	dict_size += ptr->len;
	if (ptr->code_len <= 10 && verbosity > 1) {
	  fprintf (stderr, "'%.*s'\t%lld\t%d\n", ptr->len, ptr->str, ptr->freq, ptr->code_len);
	}
      }
    }
  }
  return sum;
}