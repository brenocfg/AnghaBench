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
 int /*<<< orphan*/  M_IPID ; 
 int /*<<< orphan*/ * V_id_array ; 
 int /*<<< orphan*/ * V_id_bits ; 
 int /*<<< orphan*/  V_ip_id ; 
 int /*<<< orphan*/  V_ip_id_mtx ; 
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipid_sysuninit(void)
{

	if (V_id_array != NULL) {
		free(V_id_array, M_IPID);
		free(V_id_bits, M_IPID);
	}
	counter_u64_free(V_ip_id);
	mtx_destroy(&V_ip_id_mtx);
}