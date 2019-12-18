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
typedef  int uintmax_t ;
struct xfile {size_t xf_type; int xf_flag; int xf_count; int xf_msgcount; scalar_t__ xf_offset; scalar_t__ xf_data; scalar_t__ xf_file; } ;
typedef  int /*<<< orphan*/  dtypes ;
struct TYPE_2__ {int /*<<< orphan*/  n_value; } ;

/* Variables and functions */
 int FAPPEND ; 
 int FASYNC ; 
 int FREAD ; 
 int FWRITE ; 
 size_t NL_MAXFILES ; 
 size_t NL_NFILES ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 char* fhdr32 ; 
 char* fhdr64 ; 
 int /*<<< orphan*/  free (struct xfile*) ; 
 int getfiles (struct xfile**,size_t*) ; 
 int /*<<< orphan*/ * kd ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 int kvm_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 TYPE_1__* nl ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ totalflag ; 

__attribute__((used)) static void
filemode(void)
{
	struct xfile *fp, *buf;
	char flagbuf[16], *fbp;
	int maxf, openf;
	size_t len;
	static char const * const dtypes[] = { "???", "inode", "socket",
	    "pipe", "fifo", "kqueue", "crypto" };
	int i;
	int wid;

	if (kd != NULL) {
		if (kvm_read(kd, nl[NL_MAXFILES].n_value,
			&maxf, sizeof maxf) != sizeof maxf ||
		    kvm_read(kd, nl[NL_NFILES].n_value,
			&openf, sizeof openf) != sizeof openf)
			errx(1, "kvm_read(): %s", kvm_geterr(kd));
	} else {
		len = sizeof(int);
		if (sysctlbyname("kern.maxfiles", &maxf, &len, 0, 0) == -1 ||
		    sysctlbyname("kern.openfiles", &openf, &len, 0, 0) == -1)
			err(1, "sysctlbyname()");
	}

	if (totalflag) {
		(void)printf("%3d/%3d files\n", openf, maxf);
		return;
	}
	if (getfiles(&buf, &len) == -1)
		return;
	openf = len / sizeof *fp;

	(void)printf("%d/%d open files\n", openf, maxf);
	printf(sizeof(uintptr_t) == 4 ? fhdr32 : fhdr64);
	wid = (int)sizeof(uintptr_t) * 2;
	for (fp = (struct xfile *)buf, i = 0; i < openf; ++fp, ++i) {
		if ((size_t)fp->xf_type >= sizeof(dtypes) / sizeof(dtypes[0]))
			continue;
		(void)printf("%*jx", wid, (uintmax_t)(uintptr_t)fp->xf_file);
		(void)printf(" %-6.6s", dtypes[fp->xf_type]);
		fbp = flagbuf;
		if (fp->xf_flag & FREAD)
			*fbp++ = 'R';
		if (fp->xf_flag & FWRITE)
			*fbp++ = 'W';
		if (fp->xf_flag & FAPPEND)
			*fbp++ = 'A';
		if (fp->xf_flag & FASYNC)
			*fbp++ = 'I';
		*fbp = '\0';
		(void)printf(" %4s %3d", flagbuf, fp->xf_count);
		(void)printf(" %3d", fp->xf_msgcount);
		(void)printf(" %*jx", wid, (uintmax_t)(uintptr_t)fp->xf_data);
		(void)printf(" %*jx\n", (int)sizeof(fp->xf_offset) * 2,
		    (uintmax_t)fp->xf_offset);
	}
	free(buf);
}