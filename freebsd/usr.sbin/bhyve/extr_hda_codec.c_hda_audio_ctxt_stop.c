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
struct hda_audio_ctxt {scalar_t__ run; } ;

/* Variables and functions */

__attribute__((used)) static int
hda_audio_ctxt_stop(struct hda_audio_ctxt *actx)
{
	actx->run = 0;
	return (0);
}