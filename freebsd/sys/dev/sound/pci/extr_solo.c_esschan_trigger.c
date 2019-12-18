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
struct ess_info {int dummy; } ;
struct ess_chinfo {int /*<<< orphan*/  hwch; int /*<<< orphan*/  dir; int /*<<< orphan*/  buffer; struct ess_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
#define  PCMTRIG_ABORT 130 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int /*<<< orphan*/  ess_dmasetup (struct ess_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ess_dmatrigger (struct ess_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ess_lock (struct ess_info*) ; 
 int /*<<< orphan*/  ess_start (struct ess_chinfo*) ; 
 int /*<<< orphan*/  ess_stop (struct ess_chinfo*) ; 
 int /*<<< orphan*/  ess_unlock (struct ess_info*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
esschan_trigger(kobj_t obj, void *data, int go)
{
	struct ess_chinfo *ch = data;
	struct ess_info *sc = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return 0;

	DEB(printf("esschan_trigger: %d\n",go));

	ess_lock(sc);
	switch (go) {
	case PCMTRIG_START:
		ess_dmasetup(sc, ch->hwch, sndbuf_getbufaddr(ch->buffer), sndbuf_getsize(ch->buffer), ch->dir);
		ess_dmatrigger(sc, ch->hwch, 1);
		ess_start(ch);
		break;

	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
	default:
		ess_stop(ch);
		break;
	}
	ess_unlock(sc);
	return 0;
}