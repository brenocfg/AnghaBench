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
struct cs4231_channel {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 132 
#define  PCMTRIG_EMLDMARD 131 
#define  PCMTRIG_EMLDMAWR 130 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  cs4231_halt (struct cs4231_channel*) ; 
 int /*<<< orphan*/  cs4231_trigger (struct cs4231_channel*) ; 

__attribute__((used)) static int
cs4231_chan_trigger(kobj_t obj, void *data, int go)
{
	struct cs4231_channel *ch;

	ch = data;
	switch (go) {
	case PCMTRIG_EMLDMAWR:
	case PCMTRIG_EMLDMARD:
		break;
	case PCMTRIG_START:
		cs4231_trigger(ch);
		break;
	case PCMTRIG_ABORT:
	case PCMTRIG_STOP:
		cs4231_halt(ch);
		break;
	default:
		break;
	}

	return (0);
}