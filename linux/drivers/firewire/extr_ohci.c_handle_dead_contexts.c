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
struct fw_ohci {int it_context_support; int ir_context_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  OHCI1394_AsReqRcvContextBase ; 
 int /*<<< orphan*/  OHCI1394_AsReqTrContextBase ; 
 int /*<<< orphan*/  OHCI1394_AsRspRcvContextBase ; 
 int /*<<< orphan*/  OHCI1394_AsRspTrContextBase ; 
 int /*<<< orphan*/  OHCI1394_IsoRcvContextBase (unsigned int) ; 
 int /*<<< orphan*/  OHCI1394_IsoXmitContextBase (unsigned int) ; 
 int /*<<< orphan*/  detect_dead_context (struct fw_ohci*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static void handle_dead_contexts(struct fw_ohci *ohci)
{
	unsigned int i;
	char name[8];

	detect_dead_context(ohci, "ATReq", OHCI1394_AsReqTrContextBase);
	detect_dead_context(ohci, "ATRsp", OHCI1394_AsRspTrContextBase);
	detect_dead_context(ohci, "ARReq", OHCI1394_AsReqRcvContextBase);
	detect_dead_context(ohci, "ARRsp", OHCI1394_AsRspRcvContextBase);
	for (i = 0; i < 32; ++i) {
		if (!(ohci->it_context_support & (1 << i)))
			continue;
		sprintf(name, "IT%u", i);
		detect_dead_context(ohci, name, OHCI1394_IsoXmitContextBase(i));
	}
	for (i = 0; i < 32; ++i) {
		if (!(ohci->ir_context_support & (1 << i)))
			continue;
		sprintf(name, "IR%u", i);
		detect_dead_context(ohci, name, OHCI1394_IsoRcvContextBase(i));
	}
	/* TODO: maybe try to flush and restart the dead contexts */
}