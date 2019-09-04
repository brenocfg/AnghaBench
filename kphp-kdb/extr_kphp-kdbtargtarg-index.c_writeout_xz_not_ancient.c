#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* intree_t ;
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  z; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int ADF_NEWANCIENT ; 
 int /*<<< orphan*/  ancient_ad_users ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* get_ad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int writeout_xz_not_ancient (intree_t TC) {
  if (get_ad (TC->x)->flags & ADF_NEWANCIENT) {
    assert (TC->z);
    ancient_ad_users++;
    return 0;
  } else {
    writeout_int (TC->x);
    writeout_int (TC->z);
    return 1;
  }
}