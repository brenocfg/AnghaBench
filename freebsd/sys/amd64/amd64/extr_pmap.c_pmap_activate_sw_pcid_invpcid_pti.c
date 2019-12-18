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
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_activate_sw_pcid_pti (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_activate_sw_pti_post (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pmap_activate_sw_pcid_invpcid_pti(struct thread *td, pmap_t pmap, u_int cpuid)
{

	pmap_activate_sw_pcid_pti(pmap, cpuid, true);
	pmap_activate_sw_pti_post(td, pmap);
}