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
typedef  int /*<<< orphan*/  uintmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_DEFAULT_CREDIT ; 
 int /*<<< orphan*/  INTR_TYPE_NET ; 
 int /*<<< orphan*/  IRQ_MSGRING ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int XLP_MAX_CORES ; 
 unsigned int XLP_MAX_THREADS ; 
 int /*<<< orphan*/  cpu_establish_hardintr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  create_msgring_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgmap_lock ; 
 int /*<<< orphan*/  msgring_process_fast_intr ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nlm_is_xlp8xx_ax () ; 
 int polled ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp_cms_credit_setup (int /*<<< orphan*/ ) ; 
 unsigned int xlp_hw_thread_mask ; 
 unsigned int xlp_msg_thread_mask ; 
 int xlp_msg_threads_per_core ; 
 int xlp_threads_per_core ; 

__attribute__((used)) static void
xlp_msgring_config(void *arg)
{
	void *cookie;
	unsigned int thrmask, mask;
	int i;

	/* used polled handler for Ax silion */
	if (nlm_is_xlp8xx_ax())
		polled = 1;

	/* Don't poll on all threads, if polled */
	if (polled)
		xlp_msg_threads_per_core -= 1;

	mtx_init(&msgmap_lock, "msgring", NULL, MTX_SPIN);
	if (xlp_threads_per_core < xlp_msg_threads_per_core)
		xlp_msg_threads_per_core = xlp_threads_per_core;
	thrmask = ((1 << xlp_msg_threads_per_core) - 1);
	mask = 0;
	for (i = 0; i < XLP_MAX_CORES; i++) {
		mask <<= XLP_MAX_THREADS;
		mask |= thrmask;
	}
	xlp_msg_thread_mask = xlp_hw_thread_mask & mask;
#if 0
	printf("CMS Message handler thread mask %#jx\n",
	    (uintmax_t)xlp_msg_thread_mask);
#endif
	xlp_cms_credit_setup(CMS_DEFAULT_CREDIT);
	create_msgring_thread(0);
	cpu_establish_hardintr("msgring", msgring_process_fast_intr, NULL,
	    NULL, IRQ_MSGRING, INTR_TYPE_NET, &cookie);
}