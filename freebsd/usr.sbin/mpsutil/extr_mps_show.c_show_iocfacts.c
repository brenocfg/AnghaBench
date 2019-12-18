#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmpbuf ;
struct TYPE_5__ {int Word; } ;
struct TYPE_6__ {int IOCCapabilities; int MsgVersion; int MsgLength; int Function; int HeaderVersion; int IOCNumber; int MsgFlags; int VP_ID; int VF_ID; int IOCExceptions; int IOCStatus; int IOCLogInfo; int MaxChainDepth; int WhoInit; int NumberOfPorts; int MaxMSIxVectors; int RequestCredit; int ProductID; int IOCRequestFrameSize; int MaxInitiators; int MaxTargets; int MaxSasExpanders; int MaxEnclosures; int ProtocolFlags; int HighPriorityCredit; int MaxReplyDescriptorPostQueueDepth; int ReplyFrameSize; int MaxVolumes; int MaxDevHandle; int MaxPersistentEntries; int MinDevHandle; TYPE_1__ FWVersion; } ;
typedef  TYPE_2__ MPI2_IOC_FACTS_REPLY ;

/* Variables and functions */
 char* IOCCAP ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* mps_get_iocfacts (int) ; 
 int mps_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_parse_flags (int,char*,char*,int) ; 
 int /*<<< orphan*/  mps_unit ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
show_iocfacts(int ac, char **av)
{
	MPI2_IOC_FACTS_REPLY *facts;
	char tmpbuf[128];
	int error, fd;

	fd = mps_open(mps_unit);
	if (fd < 0) {
		error = errno;
		warn("mps_open");
		return (error);
	}

	if ((facts = mps_get_iocfacts(fd)) == NULL) {
		printf("could not get controller IOCFacts\n");
		close(fd);
		return (errno);
	}

#define IOCCAP "\3ScsiTaskFull" "\4DiagTrace" "\5SnapBuf" "\6ExtBuf" \
    "\7EEDP" "\10BiDirTarg" "\11Multicast" "\14TransRetry" "\15IR" \
    "\16EventReplay" "\17RaidAccel" "\20MSIXIndex" "\21HostDisc" \
    "\22FastPath" "\23RDPQArray" "\24AtomicReqDesc" "\25PCIeSRIOV"

	bzero(tmpbuf, sizeof(tmpbuf));
	mps_parse_flags(facts->IOCCapabilities, IOCCAP, tmpbuf, sizeof(tmpbuf));

	printf("          MsgVersion: %02d.%02d\n",
	    facts->MsgVersion >> 8, facts->MsgVersion & 0xff);
	printf("           MsgLength: %d\n", facts->MsgLength);
	printf("            Function: 0x%x\n", facts->Function);
	printf("       HeaderVersion: %02d,%02d\n",
	    facts->HeaderVersion >> 8, facts->HeaderVersion & 0xff);
	printf("           IOCNumber: %d\n", facts->IOCNumber);
	printf("            MsgFlags: 0x%x\n", facts->MsgFlags);
	printf("               VP_ID: %d\n", facts->VP_ID);
	printf("               VF_ID: %d\n", facts->VF_ID);
	printf("       IOCExceptions: %d\n", facts->IOCExceptions);
	printf("           IOCStatus: %d\n", facts->IOCStatus);
	printf("          IOCLogInfo: 0x%x\n", facts->IOCLogInfo);
	printf("       MaxChainDepth: %d\n", facts->MaxChainDepth);
	printf("             WhoInit: 0x%x\n", facts->WhoInit);
	printf("       NumberOfPorts: %d\n", facts->NumberOfPorts);
	printf("      MaxMSIxVectors: %d\n", facts->MaxMSIxVectors);
	printf("       RequestCredit: %d\n", facts->RequestCredit);
	printf("           ProductID: 0x%x\n", facts->ProductID);
	printf("     IOCCapabilities: 0x%x %s\n", facts->IOCCapabilities,
	    tmpbuf);
	printf("           FWVersion: 0x%08x\n", facts->FWVersion.Word);
	printf(" IOCRequestFrameSize: %d\n", facts->IOCRequestFrameSize);
	printf("       MaxInitiators: %d\n", facts->MaxInitiators);
	printf("          MaxTargets: %d\n", facts->MaxTargets);
	printf("     MaxSasExpanders: %d\n", facts->MaxSasExpanders);
	printf("       MaxEnclosures: %d\n", facts->MaxEnclosures);

	bzero(tmpbuf, sizeof(tmpbuf));
	mps_parse_flags(facts->ProtocolFlags,
	    "\4NvmeDevices\2ScsiTarget\1ScsiInitiator", tmpbuf, sizeof(tmpbuf));
	printf("       ProtocolFlags: 0x%x %s\n", facts->ProtocolFlags, tmpbuf);
	printf("  HighPriorityCredit: %d\n", facts->HighPriorityCredit);
	printf("MaxRepDescPostQDepth: %d\n",
	    facts->MaxReplyDescriptorPostQueueDepth);
	printf("      ReplyFrameSize: %d\n", facts->ReplyFrameSize);
	printf("          MaxVolumes: %d\n", facts->MaxVolumes);
	printf("        MaxDevHandle: %d\n", facts->MaxDevHandle);
	printf("MaxPersistentEntries: %d\n", facts->MaxPersistentEntries);
	printf("        MinDevHandle: %d\n", facts->MinDevHandle);

	free(facts);
	return (0);
}