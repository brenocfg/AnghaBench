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
struct TYPE_5__ {int handle; } ;
struct TYPE_6__ {TYPE_1__ file; } ;
struct TYPE_7__ {scalar_t__ bad; TYPE_2__ sources; int /*<<< orphan*/ * ent; } ;
typedef  TYPE_3__ isc_entropysource_t ;
typedef  int /*<<< orphan*/  isc_entropy_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int ISC_MIN (int,int) ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  entropypool_adddata (int /*<<< orphan*/ *,unsigned char*,int,int) ; 
 scalar_t__ errno ; 
 int read (int,unsigned char*,int) ; 

__attribute__((used)) static unsigned int
get_from_filesource(isc_entropysource_t *source, isc_uint32_t desired) {
	isc_entropy_t *ent = source->ent;
	unsigned char buf[128];
	int fd = source->sources.file.handle;
	ssize_t n, ndesired;
	unsigned int added;

	if (source->bad)
		return (0);

	desired = desired / 8 + (((desired & 0x07) > 0) ? 1 : 0);

	added = 0;
	while (desired > 0) {
		ndesired = ISC_MIN(desired, sizeof(buf));
		n = read(fd, buf, ndesired);
		if (n < 0) {
			if (errno == EAGAIN || errno == EINTR)
				goto out;
			goto err;
		}
		if (n == 0)
			goto err;

		entropypool_adddata(ent, buf, n, n * 8);
		added += n * 8;
		desired -= n;
	}
	goto out;

 err:
	(void)close(fd);
	source->sources.file.handle = -1;
	source->bad = ISC_TRUE;

 out:
	return (added);
}