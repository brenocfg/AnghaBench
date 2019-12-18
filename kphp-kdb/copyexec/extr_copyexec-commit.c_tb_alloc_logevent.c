#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct transaction_buffer {scalar_t__ p; scalar_t__ size; void* buff; } ;
struct lev_generic {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  lev_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void *tb_alloc_logevent (struct transaction_buffer *B, lev_type_t type, long long size) {
  size = (size + 3) & -4;
  if (B->p + size > B->size) {
    vkprintf (3, "B->p + size = %lld, B->size = %lld\n", B->p + size, B->size);
    kprintf ("Transaction buffer too small (%lld), try increase it with -M command line switch.\n", B->size);
    exit (1);
  }
  void *ptr = B->buff + B->p;
  B->p += size;
  memset (ptr, 0, size);
  struct lev_generic *E = ptr;
  E->type = type;
  return ptr;
}