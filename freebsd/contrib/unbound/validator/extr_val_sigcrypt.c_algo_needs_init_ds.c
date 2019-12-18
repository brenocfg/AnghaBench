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
typedef  size_t uint8_t ;
struct ub_packed_rrset_key {int dummy; } ;
struct algo_needs {int* needs; size_t num; } ;

/* Variables and functions */
 int ALGO_NEEDS_MAX ; 
 int /*<<< orphan*/  dnskey_algo_id_is_supported (int) ; 
 int ds_get_digest_algo (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  ds_get_key_algo (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 size_t rrset_get_count (struct ub_packed_rrset_key*) ; 

void algo_needs_init_ds(struct algo_needs* n, struct ub_packed_rrset_key* ds,
	int fav_ds_algo, uint8_t* sigalg)
{
	uint8_t algo;
	size_t i, total = 0;
	size_t num = rrset_get_count(ds);

	memset(n->needs, 0, sizeof(uint8_t)*ALGO_NEEDS_MAX);
	for(i=0; i<num; i++) {
		if(ds_get_digest_algo(ds, i) != fav_ds_algo)
			continue;
		algo = (uint8_t)ds_get_key_algo(ds, i);
		if(!dnskey_algo_id_is_supported((int)algo))
			continue;
		log_assert(algo != 0); /* we do not support 0 and is EOS */
		if(n->needs[algo] == 0) {
			n->needs[algo] = 1;
			sigalg[total] = algo;		
			total++;
		}
	}
	sigalg[total] = 0;
	n->num = total;
}