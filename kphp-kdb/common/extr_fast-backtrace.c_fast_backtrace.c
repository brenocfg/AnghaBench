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
struct stack_frame {struct stack_frame* bp; void* ip; } ;

/* Variables and functions */
 void* __libc_stack_end ; 
 struct stack_frame* get_bp () ; 

int fast_backtrace (void **buffer, int size) {
  struct stack_frame *bp = get_bp ();
  int i = 0;
  while (i < size && (void *) bp <= __libc_stack_end && !((long) bp & (sizeof (long) - 1))) {
    void *ip = bp->ip;
    buffer[i++] = ip;
    struct stack_frame *p = bp->bp;
    if (p <= bp) {
      break;
    }
    bp = p;
  }
  return i;
}