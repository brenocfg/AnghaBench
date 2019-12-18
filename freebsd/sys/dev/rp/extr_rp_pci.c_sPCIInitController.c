#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ NumAiop; scalar_t__* AiopID; int* AiopNumChan; int /*<<< orphan*/  CtlID; } ;
typedef  TYPE_1__ CONTROLLER_t ;
typedef  int /*<<< orphan*/  Byte_t ;

/* Variables and functions */
 scalar_t__ AIOPID_NULL ; 
 int /*<<< orphan*/  CLOCK_PRESC ; 
 int /*<<< orphan*/  CTLID_0001 ; 
#define  RP_DEVICE_ID_16I 136 
#define  RP_DEVICE_ID_32I 135 
#define  RP_DEVICE_ID_4J 134 
#define  RP_DEVICE_ID_4M 133 
#define  RP_DEVICE_ID_4Q 132 
#define  RP_DEVICE_ID_6M 131 
#define  RP_DEVICE_ID_8I 130 
#define  RP_DEVICE_ID_8J 129 
#define  RP_DEVICE_ID_8O 128 
 int /*<<< orphan*/  _CLK_PRE ; 
 int /*<<< orphan*/  _INDX_ADDR ; 
 int /*<<< orphan*/  _INDX_DATA ; 
 int /*<<< orphan*/  rp_writeaiop1 (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_writeaiop2 (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sPCIControllerEOI (TYPE_1__*) ; 
 scalar_t__ sReadAiopID (TYPE_1__*,int) ; 
 int sReadAiopNumChan (TYPE_1__*,int) ; 

__attribute__((used)) static int
sPCIInitController( CONTROLLER_t *CtlP,
		    int AiopNum,
		    int IRQNum,
		    Byte_t Frequency,
		    int PeriodicOnly,
		    int VendorDevice)
{
	int		i;

	CtlP->CtlID = CTLID_0001;	/* controller release 1 */

	sPCIControllerEOI(CtlP);

	/* Init AIOPs */
	CtlP->NumAiop = 0;
	for(i=0; i < AiopNum; i++)
	{
		/*device_printf(CtlP->dev, "aiop %d.\n", i);*/
		CtlP->AiopID[i] = sReadAiopID(CtlP, i);	/* read AIOP ID */
		/*device_printf(CtlP->dev, "ID = %d.\n", CtlP->AiopID[i]);*/
		if(CtlP->AiopID[i] == AIOPID_NULL)	/* if AIOP does not exist */
		{
			break;				/* done looking for AIOPs */
		}

		switch( VendorDevice ) {
		case RP_DEVICE_ID_4Q:
		case RP_DEVICE_ID_4J:
		case RP_DEVICE_ID_4M:
      			CtlP->AiopNumChan[i] = 4;
			break;
		case RP_DEVICE_ID_6M:
      			CtlP->AiopNumChan[i] = 6;
			break;
		case RP_DEVICE_ID_8O:
		case RP_DEVICE_ID_8J:
		case RP_DEVICE_ID_8I:
		case RP_DEVICE_ID_16I:
		case RP_DEVICE_ID_32I:
      			CtlP->AiopNumChan[i] = 8;
			break;
		default:
#ifdef notdef
      			CtlP->AiopNumChan[i] = 8;
#else
      			CtlP->AiopNumChan[i] = sReadAiopNumChan(CtlP, i);
#endif /* notdef */
			break;
		}
		/*device_printf(CtlP->dev, "%d channels.\n", CtlP->AiopNumChan[i]);*/
		rp_writeaiop2(CtlP, i, _INDX_ADDR,_CLK_PRE);	/* clock prescaler */
		/*device_printf(CtlP->dev, "configuring clock prescaler.\n");*/
		rp_writeaiop1(CtlP, i, _INDX_DATA,CLOCK_PRESC);
		/*device_printf(CtlP->dev, "configured clock prescaler.\n");*/
		CtlP->NumAiop++;				/* bump count of AIOPs */
	}

	if(CtlP->NumAiop == 0)
		return(-1);
	else
		return(CtlP->NumAiop);
}