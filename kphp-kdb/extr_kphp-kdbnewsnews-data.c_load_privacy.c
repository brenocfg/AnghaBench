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
struct TYPE_3__ {int priv_mask; } ;
typedef  TYPE_1__ user_t ;
typedef  int /*<<< orphan*/  index_header ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 TYPE_1__* get_user_f (int,int) ; 
 int /*<<< orphan*/  idx_fd ; 
 int read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

void load_privacy (index_header *header) {
  static int x[1 << 20];
  //assert (header->small_data_offset >= sizeof (*header));
  //assert (lseek (idx_fd, header->small_data_offset, SEEK_SET) == header->small_data_offset);
  while (1) {
    int l = read (idx_fd, x, 1 << 20);
    if (!l) {
      break;
    }
    assert ((l & 7) == 0);
    int i;
    for (i = 0; i < (l >> 3); i++) {
      if (verbosity >= 3) {
        fprintf (stderr, "uid = %d, priv_mask = %d\n", x[2 * i], x[2 * i + 1]);
      }
      user_t *U = get_user_f (x[2 * i], 1);
      U->priv_mask = x[2 * i + 1];
      assert (U->priv_mask & 1);
    }
  }
}