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

/* Variables and functions */
 int FLAG_BARE ; 
 int /*<<< orphan*/  TL_ERROR (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  wint (int) ; 

void write_var_type_flags (long long flags) {
  int new_flags = 0;
  if (flags & 1) {
    new_flags |= FLAG_BARE;
  }
  if (new_flags & FLAG_BARE) {
    TL_ERROR ("Sorry, bare vars are not (yet ?) supported.\n");
    assert (!(new_flags & FLAG_BARE));
  }
  wint (new_flags);
}