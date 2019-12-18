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
typedef  int u_char ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
 int LLCSAP_SNAP ; 
 int /*<<< orphan*/  OR_LLC ; 
 struct block* gen_bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static struct block *
gen_snap(compiler_state_t *cstate, bpf_u_int32 orgcode, bpf_u_int32 ptype)
{
	u_char snapblock[8];

	snapblock[0] = LLCSAP_SNAP;		/* DSAP = SNAP */
	snapblock[1] = LLCSAP_SNAP;		/* SSAP = SNAP */
	snapblock[2] = 0x03;			/* control = UI */
	snapblock[3] = (u_char)(orgcode >> 16);	/* upper 8 bits of organization code */
	snapblock[4] = (u_char)(orgcode >> 8);	/* middle 8 bits of organization code */
	snapblock[5] = (u_char)(orgcode >> 0);	/* lower 8 bits of organization code */
	snapblock[6] = (u_char)(ptype >> 8);	/* upper 8 bits of protocol type */
	snapblock[7] = (u_char)(ptype >> 0);	/* lower 8 bits of protocol type */
	return gen_bcmp(cstate, OR_LLC, 0, 8, snapblock);
}