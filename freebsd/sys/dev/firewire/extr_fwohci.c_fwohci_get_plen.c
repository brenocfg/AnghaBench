#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tcode_info {int hdr_len; int flag; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct fwohci_softc {TYPE_5__ fc; } ;
struct TYPE_9__ {int psize; } ;
struct fwohci_dbch {TYPE_4__ xferq; } ;
struct TYPE_7__ {size_t tcode; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_2__ common; TYPE_1__ wreqb; } ;
struct fw_pkt {TYPE_3__ mode; } ;

/* Variables and functions */
 int FWTI_BLOCK_ASY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ roundup2 (int /*<<< orphan*/ ,int) ; 
 struct tcode_info* tinfo ; 

__attribute__((used)) static int
fwohci_get_plen(struct fwohci_softc *sc, struct fwohci_dbch *dbch, struct fw_pkt *fp)
{
	struct tcode_info *info;
	int r;

	info = &tinfo[fp->mode.common.tcode];
	r = info->hdr_len + sizeof(uint32_t);
	if ((info->flag & FWTI_BLOCK_ASY) != 0)
		r += roundup2(fp->mode.wreqb.len, sizeof(uint32_t));

	if (r == sizeof(uint32_t)) {
		/* XXX */
		device_printf(sc->fc.dev, "Unknown tcode %d\n",
						fp->mode.common.tcode);
		return (-1);
	}

	if (r > dbch->xferq.psize) {
		device_printf(sc->fc.dev, "Invalid packet length %d\n", r);
		return (-1);
		/* panic ? */
	}

	return r;
}