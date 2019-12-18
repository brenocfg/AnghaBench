#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lev_start {int schema_id; int extra_bytes; int /*<<< orphan*/  str; void* split_max; void* split_min; scalar_t__ split_mod; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int schema_id; scalar_t__ split_mod; scalar_t__ split_min; scalar_t__ split_max; } ;
struct TYPE_3__ {int schema_id; scalar_t__ split_mod; scalar_t__ split_min; scalar_t__ split_max; } ;

/* Variables and functions */
 TYPE_2__* KHDR ; 
 int /*<<< orphan*/  LEV_START ; 
 TYPE_1__* ST ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binlog_existed ; 
 int /*<<< orphan*/  create_binlog_headers0 (int,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ split_max ; 
 scalar_t__ split_min ; 
 scalar_t__ split_mod ; 
 void* split_rem ; 
 struct lev_start* write_alloc (int) ; 

void start_binlog (int schema_id, char *str, int strlen) {
  int len = str ? strlen+1 : 0;
  int extra = (len + 3) & -4;
  if (len == 1) { extra = len = 0; }

  assert (!len || !str[strlen]);

  if (binlog_existed) {
    if (ST) {
      assert (ST->schema_id == schema_id && ST->split_mod == split_mod && ST->split_min == split_min && ST->split_max == split_max);
    }
    if (KHDR) {
      assert (KHDR->schema_id == schema_id && KHDR->split_mod == split_mod && KHDR->split_min == split_min && KHDR->split_max == split_max);
    }
    return;
  }

  create_binlog_headers0 (schema_id, str, strlen);

  struct lev_start *E = write_alloc (sizeof (struct lev_start) - 4 + extra);
  E->type = LEV_START;
  E->schema_id = schema_id;
  E->extra_bytes = extra;
  E->split_mod = split_mod;
  E->split_min = split_rem;
  E->split_max = split_rem + 1;
  if (len) {
    memcpy (E->str, str, len);
  }
}