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
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_probe ; 
 int /*<<< orphan*/  kld_load ; 
 int /*<<< orphan*/  kld_unload_try ; 
 int /*<<< orphan*/  linker_file_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdt_kld_load ; 
 void* sdt_kld_load_tag ; 
 int /*<<< orphan*/  sdt_kld_unload_try ; 
 void* sdt_kld_unload_try_tag ; 
 int /*<<< orphan*/  sdt_linker_file_cb ; 
 int /*<<< orphan*/  sdt_probe_func ; 
 int /*<<< orphan*/  sdt_prov_list ; 

__attribute__((used)) static void
sdt_load()
{

	TAILQ_INIT(&sdt_prov_list);

	sdt_probe_func = dtrace_probe;

	sdt_kld_load_tag = EVENTHANDLER_REGISTER(kld_load, sdt_kld_load, NULL,
	    EVENTHANDLER_PRI_ANY);
	sdt_kld_unload_try_tag = EVENTHANDLER_REGISTER(kld_unload_try,
	    sdt_kld_unload_try, NULL, EVENTHANDLER_PRI_ANY);

	/* Pick up probes from the kernel and already-loaded linker files. */
	linker_file_foreach(sdt_linker_file_cb, NULL);
}