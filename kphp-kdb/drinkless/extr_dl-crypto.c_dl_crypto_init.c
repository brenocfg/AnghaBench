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
struct TYPE_3__ {int val_n; int rand_n; int hash_st; int hash_mul; void* perm_last; void* perm_middle; void* perm_first; } ;
typedef  TYPE_1__ dl_crypto ;

/* Variables and functions */
 int N ; 
 int /*<<< orphan*/  assert (int) ; 
 void* rand_perm (int) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 

void dl_crypto_init (dl_crypto *cr, int val_n, int rand_n, int hash_st, int hash_mul, int seed) {
  assert ((N & 1) == 1);

  cr->val_n = val_n;
  cr->rand_n = rand_n;
  cr->hash_st = hash_st;
  cr->hash_mul = hash_mul;

  srand ((unsigned int)seed);
  int n = val_n + rand_n;
  cr->perm_first = rand_perm (val_n);
  cr->perm_middle = rand_perm (n);
  cr->perm_last = rand_perm (n);
}