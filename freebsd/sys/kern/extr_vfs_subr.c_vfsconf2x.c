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
typedef  int /*<<< orphan*/  xvfsp ;
struct xvfsconf {int /*<<< orphan*/ * vfc_next; int /*<<< orphan*/ * vfc_vfsops; int /*<<< orphan*/  vfc_flags; int /*<<< orphan*/  vfc_refcount; int /*<<< orphan*/  vfc_typenum; int /*<<< orphan*/  vfc_name; } ;
struct vfsconf {int /*<<< orphan*/  vfc_flags; int /*<<< orphan*/  vfc_refcount; int /*<<< orphan*/  vfc_typenum; int /*<<< orphan*/  vfc_name; } ;
struct sysctl_req {int dummy; } ;

/* Variables and functions */
 int SYSCTL_OUT (struct sysctl_req*,struct xvfsconf*,int) ; 
 int /*<<< orphan*/  bzero (struct xvfsconf*,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vfsconf2x(struct sysctl_req *req, struct vfsconf *vfsp)
{
	struct xvfsconf xvfsp;

	bzero(&xvfsp, sizeof(xvfsp));
	strcpy(xvfsp.vfc_name, vfsp->vfc_name);
	xvfsp.vfc_typenum = vfsp->vfc_typenum;
	xvfsp.vfc_refcount = vfsp->vfc_refcount;
	xvfsp.vfc_flags = vfsp->vfc_flags;
	/*
	 * These are unused in userland, we keep them
	 * to not break binary compatibility.
	 */
	xvfsp.vfc_vfsops = NULL;
	xvfsp.vfc_next = NULL;
	return (SYSCTL_OUT(req, &xvfsp, sizeof(xvfsp)));
}