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
typedef  int u32 ;
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int SEEPROM_SK ; 
 int /*<<< orphan*/  WRITE_IT_WAIT (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void CLOCK_IT (const hrz_dev *dev, u32 ctrl)
{
	// DI must be valid around rising SK edge
	WRITE_IT_WAIT(dev, ctrl & ~SEEPROM_SK);
	WRITE_IT_WAIT(dev, ctrl | SEEPROM_SK);
}