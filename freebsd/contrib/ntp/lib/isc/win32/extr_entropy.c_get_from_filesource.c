#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int isc_uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {TYPE_2__ file; } ;
struct TYPE_7__ {scalar_t__ bad; TYPE_1__ sources; int /*<<< orphan*/ * ent; } ;
typedef  TYPE_3__ isc_entropysource_t ;
typedef  int /*<<< orphan*/  isc_entropy_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;

/* Variables and functions */
 int /*<<< orphan*/  CryptGenRandom (int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ISC_MIN (int,int) ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  entropypool_adddata (int /*<<< orphan*/ *,unsigned char*,int,int) ; 

__attribute__((used)) static unsigned int
get_from_filesource(isc_entropysource_t *source, isc_uint32_t desired) {
	isc_entropy_t *ent = source->ent;
	unsigned char buf[128];
	HCRYPTPROV hcryptprov = source->sources.file.handle;
	ssize_t ndesired;
	unsigned int added;

	if (source->bad)
		return (0);

	desired = desired / 8 + (((desired & 0x07) > 0) ? 1 : 0);

	added = 0;
	while (desired > 0) {
		ndesired = ISC_MIN(desired, sizeof(buf));
		if (!CryptGenRandom(hcryptprov, ndesired, buf)) {
			CryptReleaseContext(hcryptprov, 0);
			source->bad = ISC_TRUE;
			goto out;
		}

		entropypool_adddata(ent, buf, ndesired, ndesired * 8);
		added += ndesired * 8;
		desired -= ndesired;
	}

 out:
	return (added);
}