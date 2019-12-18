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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int PFLOGIFS_MAX ; 
 struct ifnet** V_pflogifs ; 
 int /*<<< orphan*/  bpfdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_detach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 

__attribute__((used)) static void
pflog_clone_destroy(struct ifnet *ifp)
{
	int i;

	for (i = 0; i < PFLOGIFS_MAX; i++)
		if (V_pflogifs[i] == ifp)
			V_pflogifs[i] = NULL;

	bpfdetach(ifp);
	if_detach(ifp);
	if_free(ifp);
}