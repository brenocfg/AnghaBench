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
typedef  int /*<<< orphan*/  uint32_t ;
struct openpic {TYPE_1__* src; } ;
struct TYPE_2__ {int /*<<< orphan*/  ivpr; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t read_IRQreg_ivpr(struct openpic *opp, int n_IRQ)
{
	return opp->src[n_IRQ].ivpr;
}