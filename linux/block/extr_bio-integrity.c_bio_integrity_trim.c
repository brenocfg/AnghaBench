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
struct blk_integrity {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio_integrity_payload {TYPE_1__ bip_iter; } ;
struct bio {int /*<<< orphan*/  bi_disk; } ;

/* Variables and functions */
 struct bio_integrity_payload* bio_integrity (struct bio*) ; 
 int /*<<< orphan*/  bio_integrity_bytes (struct blk_integrity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 struct blk_integrity* blk_get_integrity (int /*<<< orphan*/ ) ; 

void bio_integrity_trim(struct bio *bio)
{
	struct bio_integrity_payload *bip = bio_integrity(bio);
	struct blk_integrity *bi = blk_get_integrity(bio->bi_disk);

	bip->bip_iter.bi_size = bio_integrity_bytes(bi, bio_sectors(bio));
}