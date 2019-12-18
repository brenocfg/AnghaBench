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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct smp_discover_request {int phy; int /*<<< orphan*/  ignore_zone_group; int /*<<< orphan*/  request_len; int /*<<< orphan*/  response_len; int /*<<< orphan*/  function; int /*<<< orphan*/  frame_type; } ;
struct ccb_smpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_BOTH ; 
 scalar_t__ SMP_CRC_LEN ; 
 int /*<<< orphan*/  SMP_DIS_IGNORE_ZONE_GROUP ; 
 int /*<<< orphan*/  SMP_DIS_REQUEST_LEN ; 
 int /*<<< orphan*/  SMP_DIS_RESPONSE_LEN ; 
 int /*<<< orphan*/  SMP_FRAME_TYPE_REQUEST ; 
 int /*<<< orphan*/  SMP_FUNC_DISCOVER ; 
 int /*<<< orphan*/  bzero (struct smp_discover_request*,int) ; 
 int /*<<< orphan*/  cam_fill_smpio (struct ccb_smpio*,int /*<<< orphan*/ ,void (*) (struct cam_periph*,union ccb*),int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
smp_discover(struct ccb_smpio *smpio, uint32_t retries,
	     void (*cbfcnp)(struct cam_periph *, union ccb *),
	     struct smp_discover_request *request, int request_len,
	     uint8_t *response, int response_len, int long_response,
	     int ignore_zone_group, int phy, uint32_t timeout)
{
	cam_fill_smpio(smpio,
		       retries,
		       cbfcnp,
		       /*flags*/CAM_DIR_BOTH,
		       (uint8_t *)request,
		       request_len - SMP_CRC_LEN,
		       response,
		       response_len,
		       timeout);

	bzero(request, sizeof(*request));
	request->frame_type = SMP_FRAME_TYPE_REQUEST;
	request->function = SMP_FUNC_DISCOVER;
	request->response_len = long_response ? SMP_DIS_RESPONSE_LEN : 0;
	request->request_len = long_response ? SMP_DIS_REQUEST_LEN : 0;
	if (ignore_zone_group != 0)
		request->ignore_zone_group |= SMP_DIS_IGNORE_ZONE_GROUP;
	request->phy = phy;
}