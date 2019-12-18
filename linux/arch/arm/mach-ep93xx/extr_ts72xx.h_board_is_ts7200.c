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

/* Variables and functions */
 scalar_t__ TS72XX_MODEL_TS7200 ; 
 scalar_t__ ts72xx_model () ; 

__attribute__((used)) static inline int board_is_ts7200(void)
{
	return ts72xx_model() == TS72XX_MODEL_TS7200;
}