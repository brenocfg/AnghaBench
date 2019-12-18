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
struct qce_device {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GO_SHIFT ; 
 int /*<<< orphan*/  REG_GOPROC ; 
 int /*<<< orphan*/  RESULTS_DUMP_SHIFT ; 
 int /*<<< orphan*/  qce_write (struct qce_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void qce_crypto_go(struct qce_device *qce)
{
	qce_write(qce, REG_GOPROC, BIT(GO_SHIFT) | BIT(RESULTS_DUMP_SHIFT));
}