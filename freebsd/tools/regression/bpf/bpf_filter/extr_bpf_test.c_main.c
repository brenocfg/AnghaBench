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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ BPF_NRUNS ; 
 int FAILED ; 
 int PASSED ; 
 int SIGHUP ; 
 int SIGUSR2 ; 
 scalar_t__ bpf_compile_and_filter () ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bpf_validate (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  buflen ; 
 scalar_t__ expect ; 
 scalar_t__ expect_signal ; 
 scalar_t__ invalid ; 
 scalar_t__ nins ; 
 int /*<<< orphan*/ * pc ; 
 int /*<<< orphan*/  pkt ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sig_handler ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int verbose ; 
 int /*<<< orphan*/  wirelen ; 

int
main(void)
{
#ifndef BPF_JIT_COMPILER
	u_int	i;
#endif
	u_int   ret;
	int     sig;
#ifdef BPF_VALIDATE
	int	valid;
#endif

	/* Try to catch all signals */
	for (sig = SIGHUP; sig <= SIGUSR2; sig++)
		signal(sig, sig_handler);

#ifdef BPF_VALIDATE
	valid = bpf_validate(pc, nins);
	if (valid != 0 && invalid != 0) {
		if (verbose > 1)
			printf("Validated invalid instruction(s):\t");
		if (verbose > 0)
			printf("FAILED\n");
		return (FAILED);
	} else if (valid == 0 && invalid == 0) {
		if (verbose > 1)
			printf("Invalidated valid instruction(s):\t");
		if (verbose > 0)
			printf("FAILED\n");
		return (FAILED);
	} else if (invalid != 0) {
		if (verbose > 1)
			printf("Expected and invalidated:\t");
		if (verbose > 0)
			printf("PASSED\n");
		return (PASSED);
	}
#endif

#ifdef BPF_JIT_COMPILER
	ret = bpf_compile_and_filter();
#else
	for (i = 0; i < BPF_NRUNS; i++)
		ret = bpf_filter(nins != 0 ? pc : NULL, pkt, wirelen, buflen);
#endif
	if (expect_signal != 0) {
		if (verbose > 1)
			printf("Expected signal %d but got none:\t",
			    expect_signal);
		if (verbose > 0)
			printf("FAILED\n");
		return (FAILED);
	}
	if (ret != expect) {
		if (verbose > 1)
			printf("Expected 0x%x but got 0x%x:\t", expect, ret);
		if (verbose > 0)
			printf("FAILED\n");
		return (FAILED);
	}
	if (verbose > 1)
		printf("Expected and got 0x%x:\t", ret);
	if (verbose > 0)
		printf("PASSED\n");

	return (PASSED);
}