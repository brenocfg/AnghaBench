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
struct TYPE_3__ {int /*<<< orphan*/  long_lock_secret; int /*<<< orphan*/  transaction_id; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  money_auth_code_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  md5 (unsigned char*,int,void*) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void compute_lock_codes (transaction_t *T, money_auth_code_t codes[2]) {
  static char buff[256];
  assert (T->long_lock_secret > 0);
  int L = sprintf (buff, "#Tr%lld\xcc%dXPEH", T->transaction_id, T->long_lock_secret);
  md5 ((unsigned char *) buff, L, (void *) codes);
  codes[0] ^= codes[1];
}