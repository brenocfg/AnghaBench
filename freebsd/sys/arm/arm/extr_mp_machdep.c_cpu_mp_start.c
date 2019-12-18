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

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPCPU_SIZE ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  ap_boot_mtx ; 
 int check_ap () ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 void** dpcpu ; 
 scalar_t__ kmem_malloc (int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_mp_start_ap () ; 
 int /*<<< orphan*/  printf (char*) ; 

void
cpu_mp_start(void)
{
	int error, i;

	mtx_init(&ap_boot_mtx, "ap boot", NULL, MTX_SPIN);

	/* Reserve memory for application processors */
	for(i = 0; i < (mp_ncpus - 1); i++)
		dpcpu[i] = (void *)kmem_malloc(DPCPU_SIZE, M_WAITOK | M_ZERO);

	dcache_wbinv_poc_all();

	/* Initialize boot code and start up processors */
	platform_mp_start_ap();

	/*  Check if ap's started properly */
	error = check_ap();
	if (error)
		printf("WARNING: Some AP's failed to start\n");
	else
		for (i = 1; i < mp_ncpus; i++)
			CPU_SET(i, &all_cpus);
}