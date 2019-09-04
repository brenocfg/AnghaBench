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
struct TYPE_3__ {int vidWidth; int buffWidth; int vidHeight; int buffHeight; } ;
typedef  TYPE_1__ glconfig_t ;

/* Variables and functions */

__attribute__((used)) static void SwapVidAndBuff( glconfig_t* config ) {
	int swap = config->vidWidth;
	config->vidWidth = config->buffWidth;
	config->buffWidth = swap;
	swap = config->vidHeight;
	config->vidHeight = config->buffHeight;
	config->buffHeight = swap;
}