#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfsclowner {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clopenowners; int /*<<< orphan*/  cllocalopenowners; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nfsclowner*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSCLOWNER ; 
 int /*<<< orphan*/  free (struct nfsclowner*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsow_list ; 
 TYPE_1__ nfsstatsv1 ; 

__attribute__((used)) static void
nfscl_freeopenowner(struct nfsclowner *owp, int local)
{

	LIST_REMOVE(owp, nfsow_list);
	free(owp, M_NFSCLOWNER);
	if (local)
		nfsstatsv1.cllocalopenowners--;
	else
		nfsstatsv1.clopenowners--;
}