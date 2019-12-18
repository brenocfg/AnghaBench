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
typedef  void* uint32_t ;
struct sctp_association {void* highest_tsn_inside_nr_map; void* highest_tsn_inside_map; int /*<<< orphan*/  mapping_array_base_tsn; int /*<<< orphan*/  mapping_array; int /*<<< orphan*/  nr_mapping_array; void* cumulative_tsn; } ;

/* Variables and functions */
 scalar_t__ SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CALC_TSN_TO_GAP (void*,void*,int /*<<< orphan*/ ) ; 
 int SCTP_IS_TSN_PRESENT (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SCTP_PRINTF (char*,void*,void*) ; 
 int /*<<< orphan*/  SCTP_SET_TSN_PRESENT (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ SCTP_TSN_GE (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_TSN_GT (void*,void*) ; 
 int /*<<< orphan*/  SCTP_UNSET_TSN_PRESENT (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sctp_do_drain ; 
 int /*<<< orphan*/  sctp_print_mapping_array (struct sctp_association*) ; 

__attribute__((used)) static void
sctp_mark_non_revokable(struct sctp_association *asoc, uint32_t tsn)
{
	uint32_t gap, i, cumackp1;
	int fnd = 0;
	int in_r = 0, in_nr = 0;

	if (SCTP_BASE_SYSCTL(sctp_do_drain) == 0) {
		return;
	}
	cumackp1 = asoc->cumulative_tsn + 1;
	if (SCTP_TSN_GT(cumackp1, tsn)) {
		/*
		 * this tsn is behind the cum ack and thus we don't need to
		 * worry about it being moved from one to the other.
		 */
		return;
	}
	SCTP_CALC_TSN_TO_GAP(gap, tsn, asoc->mapping_array_base_tsn);
	in_r = SCTP_IS_TSN_PRESENT(asoc->mapping_array, gap);
	in_nr = SCTP_IS_TSN_PRESENT(asoc->nr_mapping_array, gap);
	if ((in_r == 0) && (in_nr == 0)) {
#ifdef INVARIANTS
		panic("Things are really messed up now");
#else
		SCTP_PRINTF("gap:%x tsn:%x\n", gap, tsn);
		sctp_print_mapping_array(asoc);
#endif
	}
	if (in_nr == 0)
		SCTP_SET_TSN_PRESENT(asoc->nr_mapping_array, gap);
	if (in_r)
		SCTP_UNSET_TSN_PRESENT(asoc->mapping_array, gap);
	if (SCTP_TSN_GT(tsn, asoc->highest_tsn_inside_nr_map)) {
		asoc->highest_tsn_inside_nr_map = tsn;
	}
	if (tsn == asoc->highest_tsn_inside_map) {
		/* We must back down to see what the new highest is */
		for (i = tsn - 1; SCTP_TSN_GE(i, asoc->mapping_array_base_tsn); i--) {
			SCTP_CALC_TSN_TO_GAP(gap, i, asoc->mapping_array_base_tsn);
			if (SCTP_IS_TSN_PRESENT(asoc->mapping_array, gap)) {
				asoc->highest_tsn_inside_map = i;
				fnd = 1;
				break;
			}
		}
		if (!fnd) {
			asoc->highest_tsn_inside_map = asoc->mapping_array_base_tsn - 1;
		}
	}
}