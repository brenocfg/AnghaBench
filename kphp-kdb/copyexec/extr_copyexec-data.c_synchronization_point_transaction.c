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
struct lev_copyexec_aux_transaction_header {int dummy; } ;

/* Variables and functions */
 int LEV_COPYEXEC_AUX_TRANSACTION_SYNCHRONIZE ; 
 int /*<<< orphan*/  memcmp (void*,int const*,int) ; 

__attribute__((used)) static int synchronization_point_transaction (void *b, int blen) {
  const int tp = LEV_COPYEXEC_AUX_TRANSACTION_SYNCHRONIZE;
  return (blen == 24 + sizeof (struct lev_copyexec_aux_transaction_header) && !memcmp (b + sizeof (struct lev_copyexec_aux_transaction_header), &tp, 4));
}