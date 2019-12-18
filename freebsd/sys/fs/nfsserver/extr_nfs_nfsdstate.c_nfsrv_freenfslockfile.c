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
struct nfslockfile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct nfslockfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSDLOCKFILE ; 
 int /*<<< orphan*/  free (struct nfslockfile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_hash ; 

__attribute__((used)) static void
nfsrv_freenfslockfile(struct nfslockfile *lfp)
{

	LIST_REMOVE(lfp, lf_hash);
	free(lfp, M_NFSDLOCKFILE);
}