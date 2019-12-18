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
struct TYPE_3__ {int* cur; void* value64; } ;
typedef  TYPE_1__ gh_entry_t ;

/* Variables and functions */
 int GH_mode ; 
 scalar_t__ HINTS_MERGE_EXTENSION ; 
 scalar_t__ SEARCHX_EXTENSION ; 
 scalar_t__ SEARCH_EXTENSION ; 
 scalar_t__ TARG_EXTENSION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int g_desc ; 
 int g_double ; 
 void* make_value64 (int,int) ; 

__attribute__((used)) static inline void load_heap_v (gh_entry_t *H) {
  int *data = H->cur;
  int x, value;
  if (SEARCH_EXTENSION || SEARCHX_EXTENSION) {
    x = (data[1] ? data[1] : data[0]);
    value = (GH_mode & g_double ? data[2] : x);
  } else if (TARG_EXTENSION) {
    x = data[0];
    value = (GH_mode & g_double ? data[1] : x);
  } else if (HINTS_MERGE_EXTENSION) {
    x = data[0];
    value = -data[2];
    //fprintf (stderr, "(%d ; %d)\n", value, x);
  } else {
    assert (0);
  }
  if (GH_mode & g_desc) {
    /* -(-2147483648) == -2147483648 */
    H->value64 = make_value64 (-(value+1),-(x+1));
  } else {
    H->value64 = make_value64 (value, x);
  }
}