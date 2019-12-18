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
typedef  int /*<<< orphan*/  u32 ;
struct qce_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CONFIG ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int /*<<< orphan*/  qce_config_reg (struct qce_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qce_write (struct qce_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qce_setup_config(struct qce_device *qce)
{
	u32 config;

	/* get big endianness */
	config = qce_config_reg(qce, 0);

	/* clear status */
	qce_write(qce, REG_STATUS, 0);
	qce_write(qce, REG_CONFIG, config);
}