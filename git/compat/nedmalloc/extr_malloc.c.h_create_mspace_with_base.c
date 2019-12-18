#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct malloc_state {int dummy; } ;
typedef  TYPE_2__* mstate ;
typedef  int /*<<< orphan*/  mspace ;
struct TYPE_8__ {size_t page_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  sflags; } ;
struct TYPE_7__ {TYPE_1__ seg; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTERN_BIT ; 
 size_t TOP_FOOT_SIZE ; 
 int /*<<< orphan*/  ensure_initialization () ; 
 TYPE_2__* init_user_mstate (char*,size_t) ; 
 TYPE_4__ mparams ; 
 size_t pad_request (int) ; 
 int /*<<< orphan*/  set_lock (TYPE_2__*,int) ; 

mspace create_mspace_with_base(void* base, size_t capacity, int locked) {
  mstate m = 0;
  size_t msize;
  ensure_initialization();
  msize = pad_request(sizeof(struct malloc_state));
  if (capacity > msize + TOP_FOOT_SIZE &&
      capacity < (size_t) -(msize + TOP_FOOT_SIZE + mparams.page_size)) {
    m = init_user_mstate((char*)base, capacity);
    m->seg.sflags = EXTERN_BIT;
    set_lock(m, locked);
  }
  return (mspace)m;
}