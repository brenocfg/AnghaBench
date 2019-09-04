#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__** A; } ;
typedef  TYPE_2__ cf_sha3_context ;
struct TYPE_9__ {int /*<<< orphan*/  evn; int /*<<< orphan*/  odd; } ;
struct TYPE_7__ {int /*<<< orphan*/  evn; int /*<<< orphan*/  odd; } ;

/* Variables and functions */
 int /*<<< orphan*/  rho_pi_chi (TYPE_2__*) ; 
 TYPE_4__* round_constants ; 
 int /*<<< orphan*/  theta (TYPE_2__*) ; 

__attribute__((used)) static void permute(cf_sha3_context *ctx)
{
  for (int r = 0; r < 24; r++)
  {
    theta(ctx);
    rho_pi_chi(ctx);

    /* iota */
    ctx->A[0][0].odd ^= round_constants[r].odd;
    ctx->A[0][0].evn ^= round_constants[r].evn;
  }
}