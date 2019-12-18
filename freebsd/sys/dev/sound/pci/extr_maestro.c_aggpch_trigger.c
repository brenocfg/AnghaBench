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
struct agg_chinfo {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 131 
#define  PCMTRIG_EMLDMAWR 130 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  aggch_start_dac (struct agg_chinfo*) ; 
 int /*<<< orphan*/  aggch_stop_dac (struct agg_chinfo*) ; 

__attribute__((used)) static int
aggpch_trigger(kobj_t obj, void *data, int go)
{
	struct agg_chinfo *ch = data;

	switch (go) {
	case PCMTRIG_EMLDMAWR:
		break;
	case PCMTRIG_START:
		aggch_start_dac(ch);
		break;
	case PCMTRIG_ABORT:
	case PCMTRIG_STOP:
		aggch_stop_dac(ch);
		break;
	}
	return 0;
}