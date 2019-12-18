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
struct mss_info {int io_rid; int conf_rid; int drq1_rid; int drq2_rid; int password; int passwdreg; int optibase; int /*<<< orphan*/  bd_flags; int /*<<< orphan*/  bd_id; scalar_t__ irq_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BD_F_924PNP ; 
 int /*<<< orphan*/  BD_F_MSS_OFFSET ; 
 int ENXIO ; 
 int /*<<< orphan*/  MD_CS423X ; 
 int /*<<< orphan*/  MD_CS42XX ; 
 int /*<<< orphan*/  MD_GUSPNP ; 
 int /*<<< orphan*/  MD_OPTI924 ; 
 int /*<<< orphan*/  MD_OPTI925 ; 
 int /*<<< orphan*/  MD_OPTI931 ; 
 int /*<<< orphan*/  MD_VIVO ; 
 int /*<<< orphan*/  MD_YM0020 ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int azt2320_mss_mode (struct mss_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct mss_info*,int /*<<< orphan*/ ) ; 
 int isa_get_logicalid (int /*<<< orphan*/ ) ; 
 struct mss_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int mss_doattach (int /*<<< orphan*/ ,struct mss_info*) ; 
 int /*<<< orphan*/  opti_init (int /*<<< orphan*/ ,struct mss_info*) ; 

__attribute__((used)) static int
pnpmss_attach(device_t dev)
{
	struct mss_info *mss;

	mss = malloc(sizeof(*mss), M_DEVBUF, M_WAITOK | M_ZERO);
	mss->io_rid = 0;
	mss->conf_rid = -1;
	mss->irq_rid = 0;
	mss->drq1_rid = 0;
	mss->drq2_rid = 1;
	mss->bd_id = MD_CS42XX;

	switch (isa_get_logicalid(dev)) {
	case 0x0000630e:			/* CSC0000 */
	case 0x0001630e:			/* CSC0100 */
	    mss->bd_flags |= BD_F_MSS_OFFSET;
	    mss->bd_id = MD_CS423X;
	    break;

	case 0x2100a865:			/* YHM0021 */
	    mss->io_rid = 1;
	    mss->conf_rid = 4;
	    mss->bd_id = MD_YM0020;
	    break;

	case 0x1110d315:			/* ENS1011 */
	    mss->io_rid = 1;
	    mss->bd_id = MD_VIVO;
	    break;

	case 0x1093143e:			/* OPT9310 */
            mss->bd_flags |= BD_F_MSS_OFFSET;
    	    mss->conf_rid = 3;
            mss->bd_id = MD_OPTI931;
	    break;

	case 0x5092143e:			/* OPT9250 XXX guess */
            mss->io_rid = 1;
            mss->conf_rid = 3;
	    mss->bd_id = MD_OPTI925;
	    break;

	case 0x0000143e:			/* OPT0924 */
	    mss->password = 0xe5;
	    mss->passwdreg = 3;
	    mss->optibase = 0xf0c;
	    mss->io_rid = 2;
	    mss->conf_rid = 3;
	    mss->bd_id = MD_OPTI924;
	    mss->bd_flags |= BD_F_924PNP;
	    if(opti_init(dev, mss) != 0) {
		    free(mss, M_DEVBUF);
		    return ENXIO;
	    }
	    break;

	case 0x1022b839:			/* NMX2210 */
	    mss->io_rid = 1;
	    break;

	case 0x01005407:			/* AZT0001 */
	    /* put into MSS mode first (snatched from NetBSD) */
	    if (azt2320_mss_mode(mss, dev) == -1) {
		    free(mss, M_DEVBUF);
		    return ENXIO;
	    }

	    mss->bd_flags |= BD_F_MSS_OFFSET;
	    mss->io_rid = 2;
	    break;
	    
#if 0
	case 0x0000561e:			/* GRV0000 */
	    mss->bd_flags |= BD_F_MSS_OFFSET;
            mss->io_rid = 2;
            mss->conf_rid = 1;
	    mss->drq1_rid = 1;
	    mss->drq2_rid = 0;
            mss->bd_id = MD_GUSPNP;
	    break;
#endif
	case 0x01000000:			/* @@@0001 */
	    mss->drq2_rid = -1;
            break;

	/* Unknown MSS default.  We could let the CSC0000 stuff match too */
        default:
	    mss->bd_flags |= BD_F_MSS_OFFSET;
	    break;
	}
    	return mss_doattach(dev, mss);
}