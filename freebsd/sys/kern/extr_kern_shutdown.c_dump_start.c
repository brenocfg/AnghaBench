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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct kerneldumpheader {int /*<<< orphan*/  dumpextent; } ;
struct dumperinfo {int (* dumper_start ) (struct dumperinfo*) ;int blocksize; scalar_t__ mediasize; scalar_t__ mediaoffset; scalar_t__ dumpoff; scalar_t__ origdumpoff; int /*<<< orphan*/ * kdcomp; int /*<<< orphan*/  kdcrypto; } ;

/* Variables and functions */
 int E2BIG ; 
 scalar_t__ SIZEOF_METADATA ; 
 scalar_t__ dtoh64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htod64 (scalar_t__) ; 
 scalar_t__ kerneldumpcrypto_dumpkeysize (int /*<<< orphan*/ ) ; 
 int kerneldumpcrypto_init (int /*<<< orphan*/ ) ; 
 int stub1 (struct dumperinfo*) ; 

int
dump_start(struct dumperinfo *di, struct kerneldumpheader *kdh)
{
	uint64_t dumpextent, span;
	uint32_t keysize;
	int error;

#ifdef EKCD
	error = kerneldumpcrypto_init(di->kdcrypto);
	if (error != 0)
		return (error);
	keysize = kerneldumpcrypto_dumpkeysize(di->kdcrypto);
#else
	error = 0;
	keysize = 0;
#endif

	if (di->dumper_start != NULL) {
		error = di->dumper_start(di);
	} else {
		dumpextent = dtoh64(kdh->dumpextent);
		span = SIZEOF_METADATA + dumpextent + 2 * di->blocksize +
		    keysize;
		if (di->mediasize < span) {
			if (di->kdcomp == NULL)
				return (E2BIG);

			/*
			 * We don't yet know how much space the compressed dump
			 * will occupy, so try to use the whole swap partition
			 * (minus the first 64KB) in the hope that the
			 * compressed dump will fit. If that doesn't turn out to
			 * be enough, the bounds checking in dump_write()
			 * will catch us and cause the dump to fail.
			 */
			dumpextent = di->mediasize - span + dumpextent;
			kdh->dumpextent = htod64(dumpextent);
		}

		/*
		 * The offset at which to begin writing the dump.
		 */
		di->dumpoff = di->mediaoffset + di->mediasize - di->blocksize -
		    dumpextent;
	}
	di->origdumpoff = di->dumpoff;
	return (error);
}