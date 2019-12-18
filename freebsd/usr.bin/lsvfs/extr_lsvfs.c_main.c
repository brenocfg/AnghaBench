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
struct xvfsconf {char* vfc_name; char* vfc_typenum; char* vfc_refcount; int /*<<< orphan*/  vfc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASHES ; 
 char* FMT ; 
 char* HDRFMT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* fmt_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct xvfsconf*) ; 
 scalar_t__ getvfsbyname (char*,struct xvfsconf*) ; 
 struct xvfsconf* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ sysctlbyname (char*,struct xvfsconf*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char **argv)
{
  int cnt, rv = 0, i; 
  struct xvfsconf vfc, *xvfsp;
  size_t buflen;
  argc--, argv++;

  printf(HDRFMT, "Filesystem", "Num", "Refs", "Flags");
  fputs(DASHES, stdout);

  if(argc) {
    for(; argc; argc--, argv++) {
      if (getvfsbyname(*argv, &vfc) == 0) {
        printf(FMT, vfc.vfc_name, vfc.vfc_typenum, vfc.vfc_refcount,
	    fmt_flags(vfc.vfc_flags));
      } else {
	warnx("VFS %s unknown or not loaded", *argv);
        rv++;
      }
    }
  } else {
    if (sysctlbyname("vfs.conflist", NULL, &buflen, NULL, 0) < 0)
      err(1, "sysctl(vfs.conflist)");
    xvfsp = malloc(buflen);
    if (xvfsp == NULL)
      errx(1, "malloc failed");
    if (sysctlbyname("vfs.conflist", xvfsp, &buflen, NULL, 0) < 0)
      err(1, "sysctl(vfs.conflist)");
    cnt = buflen / sizeof(struct xvfsconf);

    for (i = 0; i < cnt; i++) {
      printf(FMT, xvfsp[i].vfc_name, xvfsp[i].vfc_typenum,
	    xvfsp[i].vfc_refcount, fmt_flags(xvfsp[i].vfc_flags));
    }
    free(xvfsp);
  }

  return rv;
}