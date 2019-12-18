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
struct bio_vec {int dummy; } ;
struct bio_integrity_payload {int bip_vcnt; int /*<<< orphan*/  bip_iter; int /*<<< orphan*/  bip_vec; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct bio_integrity_payload*) ; 
 int PTR_ERR (struct bio_integrity_payload*) ; 
 struct bio_integrity_payload* bio_integrity (struct bio*) ; 
 struct bio_integrity_payload* bio_integrity_alloc (struct bio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bio_integrity_clone(struct bio *bio, struct bio *bio_src,
			gfp_t gfp_mask)
{
	struct bio_integrity_payload *bip_src = bio_integrity(bio_src);
	struct bio_integrity_payload *bip;

	BUG_ON(bip_src == NULL);

	bip = bio_integrity_alloc(bio, gfp_mask, bip_src->bip_vcnt);
	if (IS_ERR(bip))
		return PTR_ERR(bip);

	memcpy(bip->bip_vec, bip_src->bip_vec,
	       bip_src->bip_vcnt * sizeof(struct bio_vec));

	bip->bip_vcnt = bip_src->bip_vcnt;
	bip->bip_iter = bip_src->bip_iter;

	return 0;
}