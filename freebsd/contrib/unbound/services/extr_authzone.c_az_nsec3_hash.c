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
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 scalar_t__ N3HASHBUFLEN ; 
 int /*<<< orphan*/  memmove (unsigned char*,int /*<<< orphan*/ *,size_t) ; 
 size_t nsec3_hash_algo_size_supported (int) ; 
 int /*<<< orphan*/  query_dname_tolower (unsigned char*) ; 
 int /*<<< orphan*/  secalgo_nsec3_hash (int,unsigned char*,size_t,unsigned char*) ; 

__attribute__((used)) static size_t
az_nsec3_hash(uint8_t* buf, size_t buflen, uint8_t* nm, size_t nmlen,
	int algo, size_t iter, uint8_t* salt, size_t saltlen)
{
	size_t hlen = nsec3_hash_algo_size_supported(algo);
	/* buffer has domain name, nsec3hash, and 256 is for max saltlen
	 * (salt has 0-255 length) */
	unsigned char p[LDNS_MAX_DOMAINLEN+1+N3HASHBUFLEN+256];
	size_t i;
	if(nmlen+saltlen > sizeof(p) || hlen+saltlen > sizeof(p))
		return 0;
	if(hlen > buflen)
		return 0; /* somehow too large for destination buffer */
	/* hashfunc(name, salt) */
	memmove(p, nm, nmlen);
	query_dname_tolower(p);
	memmove(p+nmlen, salt, saltlen);
	(void)secalgo_nsec3_hash(algo, p, nmlen+saltlen, (unsigned char*)buf);
	for(i=0; i<iter; i++) {
		/* hashfunc(hash, salt) */
		memmove(p, buf, hlen);
		memmove(p+hlen, salt, saltlen);
		(void)secalgo_nsec3_hash(algo, p, hlen+saltlen,
			(unsigned char*)buf);
	}
	return hlen;
}