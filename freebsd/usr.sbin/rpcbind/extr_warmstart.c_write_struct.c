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
typedef  scalar_t__ (* xdrproc_t ) (int /*<<< orphan*/ *,void*) ;
typedef  int mode_t ;
typedef  scalar_t__ bool_t ;
typedef  int /*<<< orphan*/  XDR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  XDR_DESTROY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDR_ENCODE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int umask (int) ; 
 int /*<<< orphan*/  xdrstdio_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool_t
write_struct(char *filename, xdrproc_t structproc, void *list)
{
	FILE *fp;
	XDR xdrs;
	mode_t omask;

	omask = umask(077);
	fp = fopen(filename, "w");
	if (fp == NULL) {
		int i;

		for (i = 0; i < 10; i++)
			close(i);
		fp = fopen(filename, "w");
		if (fp == NULL) {
			syslog(LOG_ERR,
				"cannot open file = %s for writing", filename);
			syslog(LOG_ERR, "cannot save any registration");
			return (FALSE);
		}
	}
	(void) umask(omask);
	xdrstdio_create(&xdrs, fp, XDR_ENCODE);

	if (structproc(&xdrs, list) == FALSE) {
		syslog(LOG_ERR, "rpcbind: xdr_%s: failed", filename);
		fclose(fp);
		return (FALSE);
	}
	XDR_DESTROY(&xdrs);
	fclose(fp);
	return (TRUE);
}