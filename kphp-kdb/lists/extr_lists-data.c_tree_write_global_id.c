#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_ext_small_t ;
typedef  int /*<<< orphan*/  global_id_t ;
struct TYPE_2__ {int /*<<< orphan*/  global_id; } ;

/* Variables and functions */
 TYPE_1__* LPAYLOAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_long (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tree_write_global_id (tree_ext_small_t *T) {
  if (sizeof (global_id_t) == sizeof (int)) {
    writeout_int (LPAYLOAD(T)->global_id);
  } else if (sizeof (global_id_t) == sizeof (long long)) {
    writeout_long (LPAYLOAD(T)->global_id);
  } else {
    assert (0);
  }
  return 0;
}