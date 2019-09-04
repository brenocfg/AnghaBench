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
struct lev_start {scalar_t__ schema_id; int extra_bytes; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ CACHE_SCHEMA_V1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cache_id ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 scalar_t__ log_split_max ; 
 scalar_t__ log_split_min ; 
 scalar_t__ log_split_mod ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int cache_le_start (struct lev_start *E) {
  if (E->schema_id != CACHE_SCHEMA_V1) {
    kprintf ("LEV_START schema_id isn't to CACHE_SCHEMA_V1.\n");
    return -1;
  }
  if (E->extra_bytes < 4) {
    kprintf ("LEV_START extra_bytes isn't equal to 4.\n");
    return -1;
  }
  log_split_min = E->split_min;
  log_split_max = E->split_max;
  log_split_mod = E->split_mod;
  assert (log_split_mod > 0 && log_split_min >= 0 && log_split_min + 1 ==  log_split_max && log_split_max <= log_split_mod);

  memcpy (&cache_id, E->str, 4);

  return 0;
}