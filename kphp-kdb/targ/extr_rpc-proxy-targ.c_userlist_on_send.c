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
struct gather {int dummy; } ;

/* Variables and functions */
 int* Q ; 
 int /*<<< orphan*/  QBefore ; 
 int /*<<< orphan*/  QBeforeSize ; 
 int* QN ; 
 int /*<<< orphan*/  Q_userlist ; 
 int* Qf ; 
 int* Qs ; 
 int /*<<< orphan*/  assert (int) ; 
 int default_gather_on_send (struct gather*,int) ; 
 int /*<<< orphan*/  tl_copy_through (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_unread () ; 
 int /*<<< orphan*/  tl_store_int (int) ; 
 int /*<<< orphan*/  tl_store_raw_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int userlist_on_send (struct gather *G, int n) {
  if (!Q_userlist) {
    return default_gather_on_send (G, n);
  } else {
    if (!Qs[n]) {
      return -1;
    } else {
      tl_store_raw_data (QBefore, QBeforeSize);
      int m = Qf[n];
      int cc = 0;
      tl_store_int (Qs[n]);
      while (m != -1) {
        tl_store_int (Q[m]);
        m = QN[m];
        cc ++;
      }
      assert (cc == Qs[n]);
      tl_copy_through (tl_fetch_unread (), 0);
      return 0;
    }
  }
}