#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  ccb_state; int /*<<< orphan*/ * ccb_bp; } ;
union ccb {TYPE_1__ ccb_h; int /*<<< orphan*/  csio; } ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct scsi_mode_header_6 {int dummy; } ;
struct scsi_mode_blk_desc {int dummy; } ;
struct page_element_address_assignment {int dummy; } ;
struct ch_softc {int state; int quirks; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_CCB_PROBE ; 
 int /*<<< orphan*/  CH_ELEMENT_ADDR_ASSIGN_PAGE ; 
 int CH_Q_NO_DBD ; 
#define  CH_STATE_NORMAL 129 
#define  CH_STATE_PROBE 128 
 int /*<<< orphan*/  CH_TIMEOUT_MODE_SENSE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_SCSICH ; 
 int /*<<< orphan*/  SMS_PAGE_CTRL_CURRENT ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  chdone ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  scsi_mode_sense (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static void
chstart(struct cam_periph *periph, union ccb *start_ccb)
{
	struct ch_softc *softc;

	softc = (struct ch_softc *)periph->softc;

	switch (softc->state) {
	case CH_STATE_NORMAL:
	{
		xpt_release_ccb(start_ccb);
		break;
	}
	case CH_STATE_PROBE:
	{
		int mode_buffer_len;
		void *mode_buffer;

		/*
		 * Include the block descriptor when calculating the mode
		 * buffer length,
		 */
		mode_buffer_len = sizeof(struct scsi_mode_header_6) +
				  sizeof(struct scsi_mode_blk_desc) +
				 sizeof(struct page_element_address_assignment);

		mode_buffer = malloc(mode_buffer_len, M_SCSICH, M_NOWAIT);

		if (mode_buffer == NULL) {
			printf("chstart: couldn't malloc mode sense data\n");
			break;
		}
		bzero(mode_buffer, mode_buffer_len);

		/*
		 * Get the element address assignment page.
		 */
		scsi_mode_sense(&start_ccb->csio,
				/* retries */ 1,
				/* cbfcnp */ chdone,
				/* tag_action */ MSG_SIMPLE_Q_TAG,
				/* dbd */ (softc->quirks & CH_Q_NO_DBD) ?
					FALSE : TRUE,
				/* pc */ SMS_PAGE_CTRL_CURRENT,
				/* page */ CH_ELEMENT_ADDR_ASSIGN_PAGE,
				/* param_buf */ (u_int8_t *)mode_buffer,
				/* param_len */ mode_buffer_len,
				/* sense_len */ SSD_FULL_SIZE,
				/* timeout */ CH_TIMEOUT_MODE_SENSE);

		start_ccb->ccb_h.ccb_bp = NULL;
		start_ccb->ccb_h.ccb_state = CH_CCB_PROBE;
		xpt_action(start_ccb);
		break;
	}
	}
}