#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct aead_alg {int dummy; } ;
struct TYPE_4__ {TYPE_1__* viodev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int crypto_register_aead (struct aead_alg*) ; 
 scalar_t__ nx_check_props (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ nx_driver ; 

__attribute__((used)) static int nx_register_aead(struct aead_alg *alg, u32 fc, u32 mode)
{
	return nx_check_props(&nx_driver.viodev->dev, fc, mode) ?
	       crypto_register_aead(alg) : 0;
}