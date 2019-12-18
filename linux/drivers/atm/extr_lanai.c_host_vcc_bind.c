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
typedef  size_t vci_t ;
struct lanai_vcc {size_t vci; int /*<<< orphan*/ * vbase; } ;
struct lanai_dev {struct lanai_vcc** vccs; int /*<<< orphan*/  conf1; int /*<<< orphan*/  nbound; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG1_POWERDOWN ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/ * cardvcc_addr (struct lanai_dev*,size_t) ; 
 int /*<<< orphan*/  conf1_write (struct lanai_dev*) ; 
 int /*<<< orphan*/  conf2_write (struct lanai_dev*) ; 

__attribute__((used)) static inline void host_vcc_bind(struct lanai_dev *lanai,
	struct lanai_vcc *lvcc, vci_t vci)
{
	if (lvcc->vbase != NULL)
		return;    /* We already were bound in the other direction */
	DPRINTK("Binding vci %d\n", vci);
#ifdef USE_POWERDOWN
	if (lanai->nbound++ == 0) {
		DPRINTK("Coming out of powerdown\n");
		lanai->conf1 &= ~CONFIG1_POWERDOWN;
		conf1_write(lanai);
		conf2_write(lanai);
	}
#endif
	lvcc->vbase = cardvcc_addr(lanai, vci);
	lanai->vccs[lvcc->vci = vci] = lvcc;
}