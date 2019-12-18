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
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 scalar_t__ ETHERTYPE_PPPOED ; 
 struct block* gen_linktype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct block *
gen_pppoed(compiler_state_t *cstate)
{
	/* check for PPPoE discovery */
	return gen_linktype(cstate, (bpf_int32)ETHERTYPE_PPPOED);
}