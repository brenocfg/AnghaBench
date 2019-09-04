#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lev_dns_delete_records {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ qtype; scalar_t__ name_len; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ record_t ;

/* Variables and functions */
 scalar_t__ LEV_DNS_DELETE_RECORDS ; 
 struct lev_dns_delete_records* alloc_log_event (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cmp_str (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int compute_uncommitted_log_bytes () ; 
 int /*<<< orphan*/  delete_logevents ; 
 int /*<<< orphan*/  flush_binlog_forced (int /*<<< orphan*/ ) ; 
 TYPE_1__* last_deleted_record ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  try_change_zone () ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void record_delete (record_t *r) {
  if (last_deleted_record && !cmp_str (last_deleted_record->name, last_deleted_record->name_len, r->name, r->name_len) && last_deleted_record->qtype == r->qtype) {
    return;
  }

  try_change_zone ();
  vkprintf (3, "Delete records for name '%.*s' of type %d.\n", r->name_len, r->name, r->qtype);
  struct lev_dns_delete_records *E = alloc_log_event (LEV_DNS_DELETE_RECORDS + r->name_len, sizeof (struct lev_dns_delete_records) + r->name_len, r->qtype);
  memcpy (E->name, r->name, r->name_len);
  last_deleted_record = r;
  if (compute_uncommitted_log_bytes () > (1 << 23)) {
    flush_binlog_forced (0);
  }
  delete_logevents++;
}