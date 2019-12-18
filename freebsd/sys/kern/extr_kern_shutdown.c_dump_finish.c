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
struct kerneldumpheader {scalar_t__ parity; int /*<<< orphan*/  dumplength; } ;
struct dumperinfo {TYPE_1__* kdcomp; scalar_t__ origdumpoff; scalar_t__ dumpoff; int /*<<< orphan*/  blocksize; int /*<<< orphan*/ * blockbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  kdc_stream; scalar_t__ kdc_resid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int compressor_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compressor_reset (int /*<<< orphan*/ ) ; 
 int dump_write (struct dumperinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int dump_write_headers (struct dumperinfo*,struct kerneldumpheader*) ; 
 int /*<<< orphan*/  htod64 (scalar_t__) ; 
 scalar_t__ kerneldump_parity (struct kerneldumpheader*) ; 

int
dump_finish(struct dumperinfo *di, struct kerneldumpheader *kdh)
{
	int error;

	if (di->kdcomp != NULL) {
		error = compressor_flush(di->kdcomp->kdc_stream);
		if (error == EAGAIN) {
			/* We have residual data in di->blockbuf. */
			error = dump_write(di, di->blockbuf, 0, di->dumpoff,
			    di->blocksize);
			di->dumpoff += di->kdcomp->kdc_resid;
			di->kdcomp->kdc_resid = 0;
		}
		if (error != 0)
			return (error);

		/*
		 * We now know the size of the compressed dump, so update the
		 * header accordingly and recompute parity.
		 */
		kdh->dumplength = htod64(di->dumpoff - di->origdumpoff);
		kdh->parity = 0;
		kdh->parity = kerneldump_parity(kdh);

		compressor_reset(di->kdcomp->kdc_stream);
	}

	error = dump_write_headers(di, kdh);
	if (error != 0)
		return (error);

	(void)dump_write(di, NULL, 0, 0, 0);
	return (0);
}