#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct atmel_tdes_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  iclk; struct ablkcipher_request* req; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct ablkcipher_request {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDES_FLAGS_BUSY ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static void atmel_tdes_finish_req(struct atmel_tdes_dev *dd, int err)
{
	struct ablkcipher_request *req = dd->req;

	clk_disable_unprepare(dd->iclk);

	dd->flags &= ~TDES_FLAGS_BUSY;

	req->base.complete(&req->base, err);
}