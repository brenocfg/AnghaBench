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
struct TYPE_3__ {int* cur; int value64; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */
 int Q_DOUBLE ; 
 int Q_REVERSE ; 
 int Q_SEARCH ; 
 int Q_UNION ; 
 int Q_order ; 
 int /*<<< orphan*/  assert (int) ; 
 void* make_value64 (int,int) ; 

__attribute__((used)) static inline void load_heap_v (gh_entry_t *H) {
  if (Q_order & Q_UNION) {
    int *data = H->cur;
    int x /*, value*/;
    x = data[0];
    //value = (Q_order & Q_DOUBLE) ? data[1] : x;

    //if (Q_order & Q_SECOND) {
    //  int t = value; value = x; x = t;
    //}
    if (Q_order & Q_REVERSE) {
      /* -(-2147483648) == -2147483648 */
      H->value64 = x;
      //H->value64 = make_value64 (-(value+1),-(x+1));
      //H->value64 = make_value64 (-(value+1),-(x+1));
    } else {
      H->value64 = -x;
      //H->value64 = make_value64 (value, x);
    }
  } else {
    assert (Q_order & Q_SEARCH);
    int *data = H->cur;
    int x, value;
    x = data[0];
    value = (Q_order & Q_DOUBLE) ? data[1] : x;
  
    if (Q_order & Q_REVERSE) {
      /* -(-2147483648) == -2147483648 */
      H->value64 = make_value64 (-(value+1),-(x+1));
    } else {
      H->value64 = make_value64 (value, x);
    }
  }
}