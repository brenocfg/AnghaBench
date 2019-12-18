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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct disklabel {int d_type; int d_subtype; int d_sparespertrack; int d_sparespercyl; int d_rpm; int d_interleave; int d_trackskew; int d_cylskew; int d_npartitions; int /*<<< orphan*/ * d_partitions; int /*<<< orphan*/  d_sbsize; int /*<<< orphan*/  d_bbsize; int /*<<< orphan*/  d_magic2; int /*<<< orphan*/ * d_spare; int /*<<< orphan*/ * d_drivedata; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_trkseek; int /*<<< orphan*/  d_headswitch; int /*<<< orphan*/  d_acylinders; int /*<<< orphan*/  d_secperunit; int /*<<< orphan*/  d_secpercyl; int /*<<< orphan*/  d_ncylinders; int /*<<< orphan*/  d_ntracks; int /*<<< orphan*/  d_nsectors; int /*<<< orphan*/  d_secsize; int /*<<< orphan*/  d_packname; int /*<<< orphan*/  d_typename; int /*<<< orphan*/  d_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsd_partition_le_enc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int le16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16enc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32enc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
bsd_disklabel_le_enc(u_char *ptr, struct disklabel *d)
{
	int i;
	u_char *p, *pe;
	uint16_t sum;

	le32enc(ptr + 0, d->d_magic);
	le16enc(ptr + 4, d->d_type);
	le16enc(ptr + 6, d->d_subtype);
	bcopy(d->d_typename, ptr + 8, 16);
	bcopy(d->d_packname, ptr + 24, 16);
	le32enc(ptr + 40, d->d_secsize);
	le32enc(ptr + 44, d->d_nsectors);
	le32enc(ptr + 48, d->d_ntracks);
	le32enc(ptr + 52, d->d_ncylinders);
	le32enc(ptr + 56, d->d_secpercyl);
	le32enc(ptr + 60, d->d_secperunit);
	le16enc(ptr + 64, d->d_sparespertrack);
	le16enc(ptr + 66, d->d_sparespercyl);
	le32enc(ptr + 68, d->d_acylinders);
	le16enc(ptr + 72, d->d_rpm);
	le16enc(ptr + 74, d->d_interleave);
	le16enc(ptr + 76, d->d_trackskew);
	le16enc(ptr + 78, d->d_cylskew);
	le32enc(ptr + 80, d->d_headswitch);
	le32enc(ptr + 84, d->d_trkseek);
	le32enc(ptr + 88, d->d_flags);
	le32enc(ptr + 92, d->d_drivedata[0]);
	le32enc(ptr + 96, d->d_drivedata[1]);
	le32enc(ptr + 100, d->d_drivedata[2]);
	le32enc(ptr + 104, d->d_drivedata[3]);
	le32enc(ptr + 108, d->d_drivedata[4]);
	le32enc(ptr + 112, d->d_spare[0]);
	le32enc(ptr + 116, d->d_spare[1]);
	le32enc(ptr + 120, d->d_spare[2]);
	le32enc(ptr + 124, d->d_spare[3]);
	le32enc(ptr + 128, d->d_spare[4]);
	le32enc(ptr + 132, d->d_magic2);
	le16enc(ptr + 136, 0);
	le16enc(ptr + 138, d->d_npartitions);
	le32enc(ptr + 140, d->d_bbsize);
	le32enc(ptr + 144, d->d_sbsize);
	for (i = 0; i < d->d_npartitions; i++)
		bsd_partition_le_enc(ptr + 148 + 16 * i, &d->d_partitions[i]);
	pe = ptr + 148 + 16 * d->d_npartitions;
	sum = 0;
	for (p = ptr; p < pe; p += 2)
		sum ^= le16dec(p);
	le16enc(ptr + 136, sum);
}