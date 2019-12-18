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
struct timer_list {int dummy; } ;
struct TYPE_4__ {TYPE_1__* aud; int /*<<< orphan*/  dmacon; } ;
struct TYPE_3__ {int /*<<< orphan*/  audper; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAF_AUD2 ; 
 int /*<<< orphan*/  amiga_audio_period ; 
 TYPE_2__ custom ; 

__attribute__((used)) static void nosound(struct timer_list *unused)
{
	/* turn off DMA for audio channel 2 */
	custom.dmacon = DMAF_AUD2;
	/* restore period to previous value after beeping */
	custom.aud[2].audper = amiga_audio_period;
}