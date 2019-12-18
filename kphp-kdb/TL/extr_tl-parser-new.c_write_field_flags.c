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
 long long FLAG_EXCL ; 
 long long FLAG_OPT_FIELD ; 
 int FLAG_OPT_VAR ; 
 int /*<<< orphan*/  wint (int) ; 

void write_field_flags (long long flags) {
  int new_flags = 0;
  //fprintf (stderr, "%lld\n", flags);
  if (flags & 1) {
    new_flags |= FLAG_BARE;
  }
  if (flags & 32) {
    new_flags |= FLAG_OPT_VAR;
  }
  if (flags & FLAG_EXCL) {
    new_flags |= FLAG_EXCL;
  }
  if (flags & FLAG_OPT_FIELD) {
   // new_flags |= FLAG_OPT_FIELD;
    new_flags |= 2;
  }
  if (flags & (1 << 21)) {
    new_flags |= 4;
  }
  wint (new_flags);
}