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
struct idrent {int noff; TYPE_1__* isoent; } ;
struct TYPE_2__ {int ext_off; scalar_t__ ext_len; scalar_t__ id_len; scalar_t__ identifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,scalar_t__) ; 

__attribute__((used)) static void
idr_extend_identifier(struct idrent *wnp, int numsize, int nullsize)
{
	unsigned char *p;
	int wnp_ext_off;

	wnp_ext_off = wnp->isoent->ext_off;
	if (wnp->noff + numsize != wnp_ext_off) {
		p = (unsigned char *)wnp->isoent->identifier;
		/* Extend the filename; foo.c --> foo___.c */
		memmove(p + wnp->noff + numsize, p + wnp_ext_off,
		    wnp->isoent->ext_len + nullsize);
		wnp->isoent->ext_off = wnp_ext_off = wnp->noff + numsize;
		wnp->isoent->id_len = wnp_ext_off + wnp->isoent->ext_len;
	}
}