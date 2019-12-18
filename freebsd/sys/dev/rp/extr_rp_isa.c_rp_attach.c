#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_9__ {int NumAiop; } ;
typedef  TYPE_1__ CONTROLLER_t ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ_DIS ; 
 int /*<<< orphan*/  MAX_AIOPS_PER_BOARD ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int rp_attachcommon (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  rp_controller ; 
 int /*<<< orphan*/  rp_isareleaseresource (TYPE_1__*) ; 
 int /*<<< orphan*/  sEnAiop (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ sGetAiopNumChan (TYPE_1__*,int) ; 
 int sInitController (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sResetAiopByNum (TYPE_1__*,int) ; 

__attribute__((used)) static int
rp_attach(device_t dev)
{
	int	unit;
	int	num_ports, num_aiops;
	int	aiop;
	CONTROLLER_t	*ctlp;
	int	retval;

	unit = device_get_unit(dev);

	ctlp = device_get_softc(dev);

#ifdef notdef
	num_aiops = sInitController(ctlp,
				rp_controller,
				MAX_AIOPS_PER_BOARD, 0,
				FREQ_DIS, 0);
#else
	num_aiops = ctlp->NumAiop;
#endif /* notdef */

	num_ports = 0;
	for(aiop=0; aiop < num_aiops; aiop++) {
		sResetAiopByNum(ctlp, aiop);
		sEnAiop(rp_controller, ctlp, aiop);
		num_ports += sGetAiopNumChan(ctlp, aiop);
	}

	retval = rp_attachcommon(ctlp, num_aiops, num_ports);
	if (retval != 0)
		goto nogo;

	return (0);

nogo:
	rp_isareleaseresource(ctlp);

	return (retval);
}