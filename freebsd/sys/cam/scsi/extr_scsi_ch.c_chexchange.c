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
union ccb {int /*<<< orphan*/  csio; } ;
typedef  int u_int16_t ;
struct changer_exchange {size_t ce_srctype; size_t ce_fdsttype; size_t ce_sdsttype; int ce_srcunit; int ce_fdstunit; int ce_sdstunit; int ce_flags; } ;
struct ch_softc {int* sc_counts; int* sc_exchangemask; int* sc_firsts; int /*<<< orphan*/  device_stats; int /*<<< orphan*/  sc_picker; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  CAM_RETRY_SELTO ; 
 int CE_INVERT1 ; 
 int CE_INVERT2 ; 
 size_t CHET_DT ; 
 int /*<<< orphan*/  CH_TIMEOUT_EXCHANGE_MEDIUM ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  SF_RETRY_UA ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 union ccb* cam_periph_getccb (struct cam_periph*,int /*<<< orphan*/ ) ; 
 int cam_periph_runccb (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chdone ; 
 int /*<<< orphan*/  cherror ; 
 int /*<<< orphan*/  scsi_exchange_medium (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static int
chexchange(struct cam_periph *periph, struct changer_exchange *ce)
{
	struct ch_softc *softc;
	u_int16_t src, dst1, dst2;
	union ccb *ccb;
	int error;

	error = 0;
	softc = (struct ch_softc *)periph->softc;
	/*
	 * Check arguments.
	 */
	if ((ce->ce_srctype > CHET_DT) || (ce->ce_fdsttype > CHET_DT) ||
	    (ce->ce_sdsttype > CHET_DT))
		return (EINVAL);
	if ((ce->ce_srcunit > (softc->sc_counts[ce->ce_srctype] - 1)) ||
	    (ce->ce_fdstunit > (softc->sc_counts[ce->ce_fdsttype] - 1)) ||
	    (ce->ce_sdstunit > (softc->sc_counts[ce->ce_sdsttype] - 1)))
		return (ENODEV);

	/*
	 * Check the request against the changer's capabilities.
	 */
	if (((softc->sc_exchangemask[ce->ce_srctype] &
	     (1 << ce->ce_fdsttype)) == 0) ||
	    ((softc->sc_exchangemask[ce->ce_fdsttype] &
	     (1 << ce->ce_sdsttype)) == 0))
		return (ENODEV);

	/*
	 * Calculate the source and destination elements.
	 */
	src = softc->sc_firsts[ce->ce_srctype] + ce->ce_srcunit;
	dst1 = softc->sc_firsts[ce->ce_fdsttype] + ce->ce_fdstunit;
	dst2 = softc->sc_firsts[ce->ce_sdsttype] + ce->ce_sdstunit;

	ccb = cam_periph_getccb(periph, CAM_PRIORITY_NORMAL);

	scsi_exchange_medium(&ccb->csio,
			     /* retries */ 1,
			     /* cbfcnp */ chdone,
			     /* tag_action */ MSG_SIMPLE_Q_TAG,
			     /* tea */ softc->sc_picker,
			     /* src */ src,
			     /* dst1 */ dst1,
			     /* dst2 */ dst2,
			     /* invert1 */ (ce->ce_flags & CE_INVERT1) ?
			                   TRUE : FALSE,
			     /* invert2 */ (ce->ce_flags & CE_INVERT2) ?
			                   TRUE : FALSE,
			     /* sense_len */ SSD_FULL_SIZE,
			     /* timeout */ CH_TIMEOUT_EXCHANGE_MEDIUM);

	error = cam_periph_runccb(ccb, cherror, /*cam_flags*/CAM_RETRY_SELTO,
				  /*sense_flags*/ SF_RETRY_UA,
				  softc->device_stats);

	xpt_release_ccb(ccb);

	return(error);
}