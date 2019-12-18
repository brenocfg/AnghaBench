#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct mpr_softc {int dummy; } ;
struct mpr_command {int cm_flags; int /*<<< orphan*/  cm_chain_list; scalar_t__ cm_req; } ;
struct mpr_chain {scalar_t__ chain; } ;
struct TYPE_6__ {int Flags; int NextChainOffset; int /*<<< orphan*/  Length; int /*<<< orphan*/  Address; } ;
struct TYPE_5__ {int Flags; int /*<<< orphan*/  Address; int /*<<< orphan*/  Length; } ;
struct TYPE_4__ {int /*<<< orphan*/  FlagsLength; int /*<<< orphan*/  Address; } ;
typedef  TYPE_1__ MPI2_SGE_SIMPLE64 ;
typedef  int /*<<< orphan*/  MPI2_REQUEST_HEADER ;
typedef  TYPE_2__ MPI2_IEEE_SGE_SIMPLE64 ;
typedef  TYPE_3__ MPI25_IEEE_SGE_CHAIN64 ;

/* Variables and functions */
 int MPI25_IEEE_SGE_FLAGS_END_OF_LIST ; 
 int MPI2_IEEE_SGE_FLAGS_CHAIN_ELEMENT ; 
 int MPI2_SGE_FLAGS_END_OF_BUFFER ; 
 int MPI2_SGE_FLAGS_END_OF_LIST ; 
 int MPI2_SGE_FLAGS_SHIFT ; 
 int MPR_CM_FLAGS_SGE_SIMPLE ; 
 struct mpr_chain* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct mpr_chain* TAILQ_NEXT (struct mpr_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chain_link ; 
 int /*<<< orphan*/  hexdump (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpr_to_u64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
mpr_print_sgl(struct mpr_softc *sc, struct mpr_command *cm, int offset)
{
	MPI2_IEEE_SGE_SIMPLE64 *ieee_sge;
	MPI25_IEEE_SGE_CHAIN64 *ieee_sgc;
	MPI2_SGE_SIMPLE64 *sge;
	MPI2_REQUEST_HEADER *req;
	struct mpr_chain *chain = NULL;
	char *frame;
	u_int i = 0, flags, length;

	req = (MPI2_REQUEST_HEADER *)cm->cm_req;
	frame = (char *)cm->cm_req;
	ieee_sge = (MPI2_IEEE_SGE_SIMPLE64 *)&frame[offset * 4];
	sge = (MPI2_SGE_SIMPLE64 *)&frame[offset * 4];
	printf("SGL for command %p\n", cm);

	hexdump(frame, 128, NULL, 0);
	while ((frame != NULL) && (!(cm->cm_flags & MPR_CM_FLAGS_SGE_SIMPLE))) {
		flags = ieee_sge->Flags;
		length = le32toh(ieee_sge->Length);
		printf("IEEE seg%d flags=0x%02x len=0x%08x addr=0x%016jx\n", i,
		    flags, length, mpr_to_u64(&ieee_sge->Address));
		if (flags & MPI25_IEEE_SGE_FLAGS_END_OF_LIST)
			break;
		ieee_sge++;
		i++;
		if (flags & MPI2_IEEE_SGE_FLAGS_CHAIN_ELEMENT) {
			ieee_sgc = (MPI25_IEEE_SGE_CHAIN64 *)ieee_sge;
			printf("IEEE chain flags=0x%x len=0x%x Offset=0x%x "
			    "Address=0x%016jx\n", ieee_sgc->Flags,
			    le32toh(ieee_sgc->Length),
			    ieee_sgc->NextChainOffset,
			    mpr_to_u64(&ieee_sgc->Address));
			if (chain == NULL)
				chain = TAILQ_FIRST(&cm->cm_chain_list);
			else
				chain = TAILQ_NEXT(chain, chain_link);
			frame = (char *)chain->chain;
			ieee_sge = (MPI2_IEEE_SGE_SIMPLE64 *)frame;
			hexdump(frame, 128, NULL, 0);
		}
	}
	while ((frame != NULL) && (cm->cm_flags & MPR_CM_FLAGS_SGE_SIMPLE)) {
		flags = le32toh(sge->FlagsLength) >> MPI2_SGE_FLAGS_SHIFT;
		printf("seg%d flags=0x%02x len=0x%06x addr=0x%016jx\n", i,
		    flags, le32toh(sge->FlagsLength) & 0xffffff,
		    mpr_to_u64(&sge->Address));
		if (flags & (MPI2_SGE_FLAGS_END_OF_LIST |
		    MPI2_SGE_FLAGS_END_OF_BUFFER))
			break;
		sge++;
		i++;
	}
}