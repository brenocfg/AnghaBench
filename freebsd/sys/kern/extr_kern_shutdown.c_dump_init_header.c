#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct kerneldumpheader {char* magic; char* architecture; char* hostname; char* versionstring; char* panicstring; int /*<<< orphan*/  parity; int /*<<< orphan*/  compression; void* blocksize; void* dumpkeysize; void* dumptime; void* dumplength; void* dumpextent; void* architectureversion; void* version; } ;
struct dumperinfo {TYPE_1__* kdcomp; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  kdcrypto; } ;
struct TYPE_4__ {char* pr_hostname; } ;
struct TYPE_3__ {int /*<<< orphan*/  kdc_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNELDUMPVERSION ; 
 char* MACHINE_ARCH ; 
 int /*<<< orphan*/  bzero (struct kerneldumpheader*,int) ; 
 void* htod32 (int /*<<< orphan*/ ) ; 
 void* htod64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kerneldump_parity (struct kerneldumpheader*) ; 
 int /*<<< orphan*/  kerneldumpcrypto_dumpkeysize (int /*<<< orphan*/ ) ; 
 char* panicstr ; 
 TYPE_2__ prison0 ; 
 size_t strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  time_second ; 
 char* version ; 

void
dump_init_header(const struct dumperinfo *di, struct kerneldumpheader *kdh,
    char *magic, uint32_t archver, uint64_t dumplen)
{
	size_t dstsize;

	bzero(kdh, sizeof(*kdh));
	strlcpy(kdh->magic, magic, sizeof(kdh->magic));
	strlcpy(kdh->architecture, MACHINE_ARCH, sizeof(kdh->architecture));
	kdh->version = htod32(KERNELDUMPVERSION);
	kdh->architectureversion = htod32(archver);
	kdh->dumplength = htod64(dumplen);
	kdh->dumpextent = kdh->dumplength;
	kdh->dumptime = htod64(time_second);
#ifdef EKCD
	kdh->dumpkeysize = htod32(kerneldumpcrypto_dumpkeysize(di->kdcrypto));
#else
	kdh->dumpkeysize = 0;
#endif
	kdh->blocksize = htod32(di->blocksize);
	strlcpy(kdh->hostname, prison0.pr_hostname, sizeof(kdh->hostname));
	dstsize = sizeof(kdh->versionstring);
	if (strlcpy(kdh->versionstring, version, dstsize) >= dstsize)
		kdh->versionstring[dstsize - 2] = '\n';
	if (panicstr != NULL)
		strlcpy(kdh->panicstring, panicstr, sizeof(kdh->panicstring));
	if (di->kdcomp != NULL)
		kdh->compression = di->kdcomp->kdc_format;
	kdh->parity = kerneldump_parity(kdh);
}