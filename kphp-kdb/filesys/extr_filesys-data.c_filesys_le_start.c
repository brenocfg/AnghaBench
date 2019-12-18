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
struct lev_start {scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; scalar_t__ split_mod; int extra_bytes; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ FILESYS_SCHEMA_V1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ log_split_max ; 
 scalar_t__ log_split_min ; 
 scalar_t__ log_split_mod ; 
 int /*<<< orphan*/  memcpy (long long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 long long volume_id ; 

__attribute__((used)) static int filesys_le_start (struct lev_start *E) {
  if (E->schema_id != FILESYS_SCHEMA_V1) {
    return -1;
  }
  long long l;
  log_split_min = E->split_min;
  log_split_max = E->split_max;
  log_split_mod = E->split_mod;
  assert (log_split_mod > 0 && log_split_min >= 0 && log_split_min + 1 ==  log_split_max && log_split_max <= log_split_mod);
  assert (E->extra_bytes == 8);
  memcpy (&l, E->str, 8);
  if (volume_id >= 0 && l != volume_id) {
    fprintf (stderr, "Binlog volume_id isn't matched.\n");
    exit (1);
  }
  volume_id = l;
  return 0;
}