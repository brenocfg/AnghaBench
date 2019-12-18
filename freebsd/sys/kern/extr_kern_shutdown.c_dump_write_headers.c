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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct kerneldumpheader {int /*<<< orphan*/  dumpextent; } ;
struct kerneldumpcrypto {void* kdc_dumpkey; } ;
struct dumperinfo {size_t blocksize; int (* dumper_hdr ) (struct dumperinfo*,struct kerneldumpheader*,void*,int) ;size_t mediaoffset; size_t mediasize; void* blockbuf; struct kerneldumpcrypto* kdcrypto; } ;

/* Variables and functions */
 int ENOMEM ; 
 int dtoh64 (int /*<<< orphan*/ ) ; 
 int dump_write (struct dumperinfo*,void*,int /*<<< orphan*/ ,int,int) ; 
 int kerneldumpcrypto_dumpkeysize (struct kerneldumpcrypto*) ; 
 int /*<<< orphan*/  memcpy (void*,struct kerneldumpheader*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int stub1 (struct dumperinfo*,struct kerneldumpheader*,void*,int) ; 

__attribute__((used)) static int
dump_write_headers(struct dumperinfo *di, struct kerneldumpheader *kdh)
{
#ifdef EKCD
	struct kerneldumpcrypto *kdc;
#endif
	void *buf, *key;
	size_t hdrsz;
	uint64_t extent;
	uint32_t keysize;
	int error;

	hdrsz = sizeof(*kdh);
	if (hdrsz > di->blocksize)
		return (ENOMEM);

#ifdef EKCD
	kdc = di->kdcrypto;
	key = kdc->kdc_dumpkey;
	keysize = kerneldumpcrypto_dumpkeysize(kdc);
#else
	key = NULL;
	keysize = 0;
#endif

	/*
	 * If the dump device has special handling for headers, let it take care
	 * of writing them out.
	 */
	if (di->dumper_hdr != NULL)
		return (di->dumper_hdr(di, kdh, key, keysize));

	if (hdrsz == di->blocksize)
		buf = kdh;
	else {
		buf = di->blockbuf;
		memset(buf, 0, di->blocksize);
		memcpy(buf, kdh, hdrsz);
	}

	extent = dtoh64(kdh->dumpextent);
#ifdef EKCD
	if (kdc != NULL) {
		error = dump_write(di, kdc->kdc_dumpkey, 0,
		    di->mediaoffset + di->mediasize - di->blocksize - extent -
		    keysize, keysize);
		if (error != 0)
			return (error);
	}
#endif

	error = dump_write(di, buf, 0,
	    di->mediaoffset + di->mediasize - 2 * di->blocksize - extent -
	    keysize, di->blocksize);
	if (error == 0)
		error = dump_write(di, buf, 0, di->mediaoffset + di->mediasize -
		    di->blocksize, di->blocksize);
	return (error);
}