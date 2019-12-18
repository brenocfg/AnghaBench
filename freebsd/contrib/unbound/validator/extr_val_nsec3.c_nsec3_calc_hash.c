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
struct regional {int dummy; } ;
struct nsec3_cached_hash {size_t dname_len; size_t hash_len; int /*<<< orphan*/ * hash; int /*<<< orphan*/ * dname; int /*<<< orphan*/  rr; int /*<<< orphan*/  nsec3; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  log_err (char*,int) ; 
 int nsec3_get_algo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t nsec3_get_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsec3_get_salt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 
 size_t nsec3_hash_algo_size_supported (int) ; 
 int /*<<< orphan*/  query_dname_tolower (scalar_t__) ; 
 scalar_t__ regional_alloc (struct regional*,size_t) ; 
 int /*<<< orphan*/  secalgo_nsec3_hash (int,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
nsec3_calc_hash(struct regional* region, sldns_buffer* buf, 
	struct nsec3_cached_hash* c)
{
	int algo = nsec3_get_algo(c->nsec3, c->rr);
	size_t iter = nsec3_get_iter(c->nsec3, c->rr);
	uint8_t* salt;
	size_t saltlen, i;
	if(!nsec3_get_salt(c->nsec3, c->rr, &salt, &saltlen))
		return -1;
	/* prepare buffer for first iteration */
	sldns_buffer_clear(buf);
	sldns_buffer_write(buf, c->dname, c->dname_len);
	query_dname_tolower(sldns_buffer_begin(buf));
	sldns_buffer_write(buf, salt, saltlen);
	sldns_buffer_flip(buf);
	c->hash_len = nsec3_hash_algo_size_supported(algo);
	if(c->hash_len == 0) {
		log_err("nsec3 hash of unknown algo %d", algo);
		return -1;
	}
	c->hash = (uint8_t*)regional_alloc(region, c->hash_len);
	if(!c->hash)
		return 0;
	(void)secalgo_nsec3_hash(algo, (unsigned char*)sldns_buffer_begin(buf),
		sldns_buffer_limit(buf), (unsigned char*)c->hash);
	for(i=0; i<iter; i++) {
		sldns_buffer_clear(buf);
		sldns_buffer_write(buf, c->hash, c->hash_len);
		sldns_buffer_write(buf, salt, saltlen);
		sldns_buffer_flip(buf);
		(void)secalgo_nsec3_hash(algo,
			(unsigned char*)sldns_buffer_begin(buf),
			sldns_buffer_limit(buf), (unsigned char*)c->hash);
	}
	return 1;
}