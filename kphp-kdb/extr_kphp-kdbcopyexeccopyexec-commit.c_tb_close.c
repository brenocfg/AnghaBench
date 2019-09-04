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
struct transaction_buffer {int /*<<< orphan*/  p; int /*<<< orphan*/  buff; } ;
struct lev_copyexec_aux_transaction_footer {int /*<<< orphan*/  sha1; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_COPYEXEC_AUX_TRANSACTION_FOOTER ; 
 int /*<<< orphan*/  SHA1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 struct lev_copyexec_aux_transaction_footer* tb_alloc_logevent (struct transaction_buffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tb_close (struct transaction_buffer *B) {
  unsigned char transaction_sha1[20];
  SHA1 (B->buff, B->p, transaction_sha1);
  struct lev_copyexec_aux_transaction_footer *E = tb_alloc_logevent (B, LEV_COPYEXEC_AUX_TRANSACTION_FOOTER, sizeof (struct lev_copyexec_aux_transaction_footer));
  memcpy (E->sha1, transaction_sha1, 20);
}