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
struct csa_info {int dummy; } ;
struct csa_chinfo {scalar_t__ dir; struct csa_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  csa_active (struct csa_info*,int) ; 
 int /*<<< orphan*/  csa_setupchan (struct csa_chinfo*) ; 
 int /*<<< orphan*/  csa_startcapturedma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_startplaydma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_stopcapturedma (struct csa_info*) ; 
 int /*<<< orphan*/  csa_stopplaydma (struct csa_info*) ; 

__attribute__((used)) static int
csachan_trigger(kobj_t obj, void *data, int go)
{
	struct csa_chinfo *ch = data;
	struct csa_info *csa = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return 0;

	if (go == PCMTRIG_START) {
		csa_active(csa, 1);
		csa_setupchan(ch);
		if (ch->dir == PCMDIR_PLAY)
			csa_startplaydma(csa);
		else
			csa_startcapturedma(csa);
	} else {
		if (ch->dir == PCMDIR_PLAY)
			csa_stopplaydma(csa);
		else
			csa_stopcapturedma(csa);
		csa_active(csa, -1);
	}
	return 0;
}