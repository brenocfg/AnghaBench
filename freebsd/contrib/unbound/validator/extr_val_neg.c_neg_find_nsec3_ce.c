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
typedef  int /*<<< orphan*/  uint8_t ;
struct val_neg_zone {scalar_t__ labs; int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  nsec3_saltlen; int /*<<< orphan*/  nsec3_salt; int /*<<< orphan*/  nsec3_iter; int /*<<< orphan*/  nsec3_hash; } ;
struct val_neg_data {scalar_t__ in_use; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  hashce ;
typedef  int /*<<< orphan*/  b32 ;

/* Variables and functions */
 int NSEC3_SHA_LEN ; 
 int /*<<< orphan*/  dname_remove_label (int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 struct val_neg_data* neg_find_data (struct val_neg_zone*,int /*<<< orphan*/ *,size_t,scalar_t__) ; 
 size_t nsec3_get_hashed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 size_t nsec3_hash_to_b32 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct val_neg_data*
neg_find_nsec3_ce(struct val_neg_zone* zone, uint8_t* qname, size_t qname_len,
		int qlabs, sldns_buffer* buf, uint8_t* hashnc, size_t* nclen)
{
	struct val_neg_data* data;
	uint8_t hashce[NSEC3_SHA_LEN];
	uint8_t b32[257];
	size_t celen, b32len;

	*nclen = 0;
	while(qlabs > 0) {
		/* hash */
		if(!(celen=nsec3_get_hashed(buf, qname, qname_len, 
			zone->nsec3_hash, zone->nsec3_iter, zone->nsec3_salt, 
			zone->nsec3_saltlen, hashce, sizeof(hashce))))
			return NULL;
		if(!(b32len=nsec3_hash_to_b32(hashce, celen, zone->name,
			zone->len, b32, sizeof(b32))))
			return NULL;

		/* lookup (exact match only) */
		data = neg_find_data(zone, b32, b32len, zone->labs+1);
		if(data && data->in_use) {
			/* found ce match! */
			return data;
		}

		*nclen = celen;
		memmove(hashnc, hashce, celen);
		dname_remove_label(&qname, &qname_len);
		qlabs --;
	}
	return NULL;
}