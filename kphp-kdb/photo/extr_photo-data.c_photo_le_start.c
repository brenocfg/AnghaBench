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
struct lev_start {scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; } ;

/* Variables and functions */
 scalar_t__ PHOTO_SCHEMA_V1 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ log_split_max ; 
 scalar_t__ log_split_min ; 
 scalar_t__ log_split_mod ; 
 int /*<<< orphan*/  try_init_local_uid () ; 

__attribute__((used)) static int photo_le_start (struct lev_start *E) {
  if (E->schema_id != PHOTO_SCHEMA_V1) {
    return -1;
  }

  log_split_min = E->split_min;
  log_split_max = E->split_max;
  log_split_mod = E->split_mod;
  assert (log_split_mod > 0 && log_split_min >= 0 && log_split_min + 1 == log_split_max && log_split_max <= log_split_mod);

  try_init_local_uid();

  return 0;
}