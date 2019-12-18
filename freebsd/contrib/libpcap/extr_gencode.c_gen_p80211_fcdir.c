#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_5__ {int linktype; } ;
typedef  TYPE_1__ compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
#define  DLT_IEEE802_11 131 
#define  DLT_IEEE802_11_RADIO 130 
#define  DLT_IEEE802_11_RADIO_AVS 129 
#define  DLT_PRISM_HEADER 128 
 scalar_t__ IEEE80211_FC1_DIR_MASK ; 
 int /*<<< orphan*/  OR_LINKHDR ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*) ; 
 struct block* gen_mcmp (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct block *
gen_p80211_fcdir(compiler_state_t *cstate, int fcdir)
{
	struct block *b0;

	switch (cstate->linktype) {

	case DLT_IEEE802_11:
	case DLT_PRISM_HEADER:
	case DLT_IEEE802_11_RADIO_AVS:
	case DLT_IEEE802_11_RADIO:
		break;

	default:
		bpf_error(cstate, "frame direction supported only with 802.11 headers");
		/* NOTREACHED */
	}

	b0 = gen_mcmp(cstate, OR_LINKHDR, 1, BPF_B, (bpf_int32)fcdir,
		(bpf_u_int32)IEEE80211_FC1_DIR_MASK);

	return (b0);
}