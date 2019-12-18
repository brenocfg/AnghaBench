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
struct sb_chinfo {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  sb_start (struct sb_chinfo*) ; 
 int /*<<< orphan*/  sb_stop (struct sb_chinfo*) ; 
 int /*<<< orphan*/  sndbuf_dma (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sbchan_trigger(kobj_t obj, void *data, int go)
{
	struct sb_chinfo *ch = data;

	if (!PCMTRIG_COMMON(go))
		return 0;

	sndbuf_dma(ch->buffer, go);
	if (go == PCMTRIG_START)
		sb_start(ch);
	else
		sb_stop(ch);
	return 0;
}