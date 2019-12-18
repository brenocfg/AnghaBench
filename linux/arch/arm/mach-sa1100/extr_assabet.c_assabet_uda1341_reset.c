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
 int /*<<< orphan*/  RST_UDA1341 ; 
 int /*<<< orphan*/  assabet_codec_reset (int /*<<< orphan*/ ,int) ; 

void assabet_uda1341_reset(int set)
{
	assabet_codec_reset(RST_UDA1341, set);
}