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
struct TYPE_4__ {int /*<<< orphan*/  tmp; int /*<<< orphan*/  ctx; int /*<<< orphan*/  x; int /*<<< orphan*/  r; int /*<<< orphan*/  m; } ;
typedef  TYPE_1__ bbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_RECP_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void bbs_free (bbs_t *self) {
  BN_free (self->m);
  BN_RECP_CTX_free (self->r);
  BN_free (self->x);
  BN_CTX_free (self->ctx);
  free (self->tmp);
  memset (self, 0, sizeof (*self));
}