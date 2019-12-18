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
struct ess_chinfo {int run; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 130 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  ess_start (struct ess_chinfo*) ; 
 int /*<<< orphan*/  ess_stop (struct ess_chinfo*) ; 
 int /*<<< orphan*/  sndbuf_dma (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
esschan_trigger(kobj_t obj, void *data, int go)
{
	struct ess_chinfo *ch = data;

	if (!PCMTRIG_COMMON(go))
		return 0;

	switch (go) {
	case PCMTRIG_START:
		ch->run = 1;
		sndbuf_dma(ch->buffer, go);
		ess_start(ch);
		break;

	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
	default:
		ess_stop(ch);
		break;
	}
	return 0;
}