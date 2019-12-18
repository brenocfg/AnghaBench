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
struct dos_partition {unsigned char dp_flag; unsigned char dp_shd; unsigned char dp_ssect; unsigned char dp_scyl; unsigned char dp_typ; unsigned char dp_ehd; unsigned char dp_esect; unsigned char dp_ecyl; int /*<<< orphan*/  dp_size; int /*<<< orphan*/  dp_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32enc (unsigned char*,int /*<<< orphan*/ ) ; 

void
dos_partition_enc(void *pp, struct dos_partition *d)
{
	unsigned char *p = pp;

	p[0] = d->dp_flag;
	p[1] = d->dp_shd;
	p[2] = d->dp_ssect;
	p[3] = d->dp_scyl;
	p[4] = d->dp_typ;
	p[5] = d->dp_ehd;
	p[6] = d->dp_esect;
	p[7] = d->dp_ecyl;
	le32enc(p + 8, d->dp_start);
	le32enc(p + 12, d->dp_size);
}