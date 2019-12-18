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
typedef  TYPE_1__* kfs_replica_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ctx_crypto; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void replica_close_ctx_crypto (kfs_replica_handle_t R) {
  if (R->ctx_crypto) {
    memset (R->ctx_crypto, 0, sizeof (*R->ctx_crypto));
    free (R->ctx_crypto);
    R->ctx_crypto = NULL;
  }
}