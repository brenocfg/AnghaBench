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
struct nicvf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NICVF_CORE_LOCK (struct nicvf*) ; 
 int /*<<< orphan*/  NICVF_CORE_UNLOCK (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_if_init_locked (struct nicvf*) ; 

__attribute__((used)) static void
nicvf_if_init(void *if_softc)
{
	struct nicvf *nic = if_softc;

	NICVF_CORE_LOCK(nic);
	nicvf_if_init_locked(nic);
	NICVF_CORE_UNLOCK(nic);
}