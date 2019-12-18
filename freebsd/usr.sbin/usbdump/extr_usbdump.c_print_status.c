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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  BDMA_ENABLE ; 
 int /*<<< orphan*/  BDMA_NO_POST_SYNC ; 
 int /*<<< orphan*/  BDMA_SETUP ; 
 int /*<<< orphan*/  BW_RECLAIMED ; 
 int /*<<< orphan*/  CAN_CANCEL_IMMED ; 
 int /*<<< orphan*/  CONTROL_ACT ; 
 int /*<<< orphan*/  CONTROL_HDR ; 
 int /*<<< orphan*/  CONTROL_STALL ; 
 int /*<<< orphan*/  CONTROL_XFR ; 
 int /*<<< orphan*/  CURR_DMA_SET ; 
 int /*<<< orphan*/  DID_CLOSE ; 
 int /*<<< orphan*/  DID_DMA_DELAY ; 
 int /*<<< orphan*/  DOING_CALLBACK ; 
 int /*<<< orphan*/  DRAINING ; 
 int /*<<< orphan*/  ISOCHRONOUS_XFR ; 
 int /*<<< orphan*/  OPEN ; 
 int /*<<< orphan*/  SHORT_FRAMES_OK ; 
 int /*<<< orphan*/  SHORT_XFER_OK ; 
 int /*<<< orphan*/  STARTED ; 
 char* STATUS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSFERRING ; 
 int /*<<< orphan*/  printf (char*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
print_status(uint32_t status)
{
	printf(" status %#x <%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s0>\n",
	    status, 
	    STATUS(status, OPEN),
	    STATUS(status, TRANSFERRING),
	    STATUS(status, DID_DMA_DELAY),
	    STATUS(status, DID_CLOSE),
	    STATUS(status, DRAINING),
	    STATUS(status, STARTED),
	    STATUS(status, BW_RECLAIMED),
	    STATUS(status, CONTROL_XFR),
	    STATUS(status, CONTROL_HDR),
	    STATUS(status, CONTROL_ACT),
	    STATUS(status, CONTROL_STALL),
	    STATUS(status, SHORT_FRAMES_OK),
	    STATUS(status, SHORT_XFER_OK),
	    STATUS(status, BDMA_ENABLE),
	    STATUS(status, BDMA_NO_POST_SYNC),
	    STATUS(status, BDMA_SETUP),
	    STATUS(status, ISOCHRONOUS_XFR),
	    STATUS(status, CURR_DMA_SET),
	    STATUS(status, CAN_CANCEL_IMMED),
	    STATUS(status, DOING_CALLBACK));
}