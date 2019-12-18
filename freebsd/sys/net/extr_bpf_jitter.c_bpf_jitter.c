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
struct bpf_jit_filter {int /*<<< orphan*/  size; int /*<<< orphan*/ * func; } ;
struct bpf_insn {int dummy; } ;
typedef  struct bpf_jit_filter bpf_jit_filter ;

/* Variables and functions */
 int /*<<< orphan*/  M_BPFJIT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/ * bpf_jit_accept_all ; 
 int /*<<< orphan*/ * bpf_jit_compile (struct bpf_insn*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct bpf_jit_filter*,...) ; 
 scalar_t__ malloc (int,...) ; 

bpf_jit_filter *
bpf_jitter(struct bpf_insn *fp, int nins)
{
	bpf_jit_filter *filter;

	/* Allocate the filter structure. */
#ifdef _KERNEL
	filter = (struct bpf_jit_filter *)malloc(sizeof(*filter),
	    M_BPFJIT, M_NOWAIT);
#else
	filter = (struct bpf_jit_filter *)malloc(sizeof(*filter));
#endif
	if (filter == NULL)
		return (NULL);

	/* No filter means accept all. */
	if (fp == NULL || nins == 0) {
		filter->func = bpf_jit_accept_all;
		return (filter);
	}

	/* Create the binary. */
	if ((filter->func = bpf_jit_compile(fp, nins, &filter->size)) == NULL) {
#ifdef _KERNEL
		free(filter, M_BPFJIT);
#else
		free(filter);
#endif
		return (NULL);
	}

	return (filter);
}