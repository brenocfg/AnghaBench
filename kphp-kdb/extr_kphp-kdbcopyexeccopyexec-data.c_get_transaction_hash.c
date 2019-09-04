#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  transaction_id; int /*<<< orphan*/  binlog_pos; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 int /*<<< orphan*/  SHA1 (unsigned char*,int,unsigned char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int base64url_encode (unsigned char*,int,char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_transaction_hash (transaction_t *T, char output[28]) {
  unsigned char a[16], b[20];
  vkprintf (4, "{0} = %lld, {1} = %d, {2} = %d\n", T->binlog_pos, T->transaction_id, T->mask);
  memcpy (a, &T->binlog_pos, 8);
  memcpy (a + 8, &T->transaction_id, 4);
  memcpy (a + 12, &T->mask, 4);
  SHA1 (a, 16, b);
  int r = base64url_encode (b, 20, output, 40);
  assert (!r);
  assert (strlen (output) == 27);
}