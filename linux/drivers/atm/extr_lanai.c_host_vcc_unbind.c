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
struct lanai_vcc {size_t vci; int /*<<< orphan*/ * vbase; } ;
struct lanai_dev {scalar_t__ nbound; int /*<<< orphan*/  conf1; int /*<<< orphan*/ ** vccs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG1_POWERDOWN ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/  conf1_write (struct lanai_dev*) ; 

__attribute__((used)) static inline void host_vcc_unbind(struct lanai_dev *lanai,
	struct lanai_vcc *lvcc)
{
	if (lvcc->vbase == NULL)
		return;	/* This vcc was never bound */
	DPRINTK("Unbinding vci %d\n", lvcc->vci);
	lvcc->vbase = NULL;
	lanai->vccs[lvcc->vci] = NULL;
#ifdef USE_POWERDOWN
	if (--lanai->nbound == 0) {
		DPRINTK("Going into powerdown\n");
		lanai->conf1 |= CONFIG1_POWERDOWN;
		conf1_write(lanai);
	}
#endif
}