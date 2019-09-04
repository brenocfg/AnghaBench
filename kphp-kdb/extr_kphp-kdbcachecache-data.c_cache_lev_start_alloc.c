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
struct lev_start {int extra_bytes; scalar_t__ split_mod; scalar_t__ split_min; scalar_t__ split_max; int /*<<< orphan*/  str; int /*<<< orphan*/  schema_id; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SCHEMA_V1 ; 
 int /*<<< orphan*/  LEV_START ; 
 int /*<<< orphan*/  assert (int) ; 
 struct lev_start* calloc (int,int) ; 
 void* log_split_min ; 
 scalar_t__ log_split_mod ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

struct lev_start *cache_lev_start_alloc (int cache_id, int *sz) {
  *sz = 28;
  struct lev_start *E = calloc (*sz, 1);
  E->type = LEV_START;
  E->schema_id = CACHE_SCHEMA_V1;
  E->extra_bytes = 4;
  E->split_mod = log_split_mod;
  E->split_min = log_split_min;
  E->split_max = log_split_min + 1;
  assert (E->split_mod > 0 && E->split_min >= 0 && E->split_min + 1 == E->split_max && E->split_max <= E->split_mod);

  memcpy (E->str, &cache_id, 4);
  return E;
}