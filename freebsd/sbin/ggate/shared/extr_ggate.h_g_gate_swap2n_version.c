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
struct g_gate_version {void* gv_error; void* gv_version; } ;

/* Variables and functions */
 void* htobe16 (void*) ; 

__attribute__((used)) static __inline void
g_gate_swap2n_version(struct g_gate_version *ver)
{

	ver->gv_version = htobe16(ver->gv_version);
	ver->gv_error = htobe16(ver->gv_error);
}