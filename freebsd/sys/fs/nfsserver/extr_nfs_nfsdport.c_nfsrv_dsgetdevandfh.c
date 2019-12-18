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
struct vnode {int dummy; } ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfsrv_dsgetsockmnt (struct vnode*,int /*<<< orphan*/ ,char*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
nfsrv_dsgetdevandfh(struct vnode *vp, NFSPROC_T *p, int *mirrorcntp,
    fhandle_t *fhp, char *devid)
{
	int buflen, error;
	char *buf;

	buflen = 1024;
	buf = malloc(buflen, M_TEMP, M_WAITOK);
	error = nfsrv_dsgetsockmnt(vp, 0, buf, &buflen, mirrorcntp, p, NULL,
	    fhp, devid, NULL, NULL, NULL, NULL, NULL, NULL);
	free(buf, M_TEMP);
	return (error);
}