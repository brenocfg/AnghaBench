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
struct sii_raid_conf {int total_sectors; int vendor_id; int version_major; int generation; int raid1_ident; void* raid_location; int /*<<< orphan*/  type; void** timestamp; scalar_t__ version_minor; } ;
struct g_consumer {TYPE_1__* provider; } ;
struct TYPE_2__ {int mediasize; int sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MD_SII ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SII_T_SPARE ; 
 void* arc4random () ; 
 int /*<<< orphan*/  free (struct sii_raid_conf*,int /*<<< orphan*/ ) ; 
 struct sii_raid_conf* malloc (int,int /*<<< orphan*/ ,int) ; 
 int sii_meta_write (struct g_consumer*,struct sii_raid_conf*) ; 

__attribute__((used)) static int
sii_meta_write_spare(struct g_consumer *cp)
{
	struct sii_raid_conf *meta;
	int error;

	meta = malloc(sizeof(*meta), M_MD_SII, M_WAITOK | M_ZERO);
	meta->total_sectors = cp->provider->mediasize /
	    cp->provider->sectorsize - 0x800;
	meta->vendor_id = 0x1095;
	meta->version_minor = 0;
	meta->version_major = 2;
	meta->timestamp[0] = arc4random();
	meta->timestamp[1] = arc4random();
	meta->timestamp[2] = arc4random();
	meta->timestamp[3] = arc4random();
	meta->timestamp[4] = arc4random();
	meta->timestamp[5] = arc4random();
	meta->type = SII_T_SPARE;
	meta->generation = 1;
	meta->raid1_ident = 0xff;
	meta->raid_location = arc4random();
	error = sii_meta_write(cp, meta);
	free(meta, M_MD_SII);
	return (error);
}