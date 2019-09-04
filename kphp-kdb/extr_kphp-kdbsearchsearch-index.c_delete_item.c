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
struct item {int extra; int rates_len; int len; scalar_t__ str; scalar_t__ mask; scalar_t__ rates; } ;

/* Variables and functions */
 int FLAG_DELETED ; 
 int /*<<< orphan*/  del_items ; 
 int deleted_text_bytes ; 
 struct item* get_item_f (long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zzfree (scalar_t__,int) ; 

__attribute__((used)) static int delete_item (long long item_id) {
  struct item *I = get_item_f (item_id, 0);
  if (!I || (I->extra & FLAG_DELETED)) { return 0; }
  I->extra |= FLAG_DELETED;
  zzfree (I->rates, I->rates_len * 4);
  I->rates = 0;
  I->mask = 0;
  I->rates_len = 0;
  zzfree (I->str, I->len+1);
  deleted_text_bytes += I->len;
  I->len = 0;
  I->str = 0;
  del_items++;
  return 1;
}