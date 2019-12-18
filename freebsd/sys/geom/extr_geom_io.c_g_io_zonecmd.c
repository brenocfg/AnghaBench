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
struct g_consumer {int dummy; } ;
struct disk_zone_rep_entry {int dummy; } ;
struct TYPE_3__ {int entries_allocated; } ;
struct TYPE_4__ {TYPE_1__ report; } ;
struct disk_zone_args {scalar_t__ zone_cmd; TYPE_2__ zone_params; } ;
struct bio {int bio_length; struct disk_zone_args bio_zone; int /*<<< orphan*/ * bio_done; int /*<<< orphan*/  bio_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ZONE ; 
 scalar_t__ DISK_ZONE_REPORT_ZONES ; 
 int /*<<< orphan*/  G_T_BIO ; 
 int /*<<< orphan*/  bcopy (struct disk_zone_args*,struct disk_zone_args*,int) ; 
 int biowait (struct bio*,char*) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,scalar_t__) ; 

int
g_io_zonecmd(struct disk_zone_args *zone_args, struct g_consumer *cp)
{
	struct bio *bp;
	int error;
	
	g_trace(G_T_BIO, "bio_zone(%d)", zone_args->zone_cmd);
	bp = g_alloc_bio();
	bp->bio_cmd = BIO_ZONE;
	bp->bio_done = NULL;
	/*
	 * XXX KDM need to handle report zone data.
	 */
	bcopy(zone_args, &bp->bio_zone, sizeof(*zone_args));
	if (zone_args->zone_cmd == DISK_ZONE_REPORT_ZONES)
		bp->bio_length =
		    zone_args->zone_params.report.entries_allocated *
		    sizeof(struct disk_zone_rep_entry);
	else
		bp->bio_length = 0;

	g_io_request(bp, cp);
	error = biowait(bp, "gzone");
	bcopy(&bp->bio_zone, zone_args, sizeof(*zone_args));
	g_destroy_bio(bp);
	return (error);
}