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
struct lev_generic {scalar_t__ a; } ;

/* Variables and functions */
 int LEV_LI_DEL_LIST ; 
 int LEV_TIMESTAMP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int mode ; 
 int /*<<< orphan*/  rd_bytes ; 
 scalar_t__ skip_timestamps ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ t_cutoff ; 
 scalar_t__ t_now ; 
 scalar_t__ undel_time_max ; 
 scalar_t__ undel_time_min ; 

__attribute__((used)) static int want_write (int type, void *ptr) {
  struct lev_generic *E = ptr;

  if (type == LEV_TIMESTAMP && E->a > t_now) {
    t_now = E->a;
    if (t_now > t_cutoff && !mode) {
      mode = 1;
      fprintf (stderr, "reached binlog time %d above cutoff time %d at read position %lld\n", t_now, t_cutoff, rd_bytes);
    }
  }

  if (t_now <= undel_time_max && t_now > undel_time_min) {
    return type != LEV_LI_DEL_LIST;
  }

  if (undel_time_max) {
    return 1;
  }

  if (type == LEV_TIMESTAMP && skip_timestamps) {
    return 0;
  }

  return mode;
}