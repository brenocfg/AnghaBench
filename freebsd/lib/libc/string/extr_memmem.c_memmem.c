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

/* Variables and functions */
 void* fourbyte_memmem (unsigned char const*,size_t,unsigned char const*) ; 
 unsigned char* memchr (void const*,unsigned char const,size_t) ; 
 void* threebyte_memmem (unsigned char const*,size_t,unsigned char const*) ; 
 void* twobyte_memmem (unsigned char const*,size_t,unsigned char const*) ; 
 void* twoway_memmem (unsigned char const*,unsigned char const*,unsigned char const*,size_t) ; 

void *memmem(const void *h0, size_t k, const void *n0, size_t l)
{
	const unsigned char *h = h0, *n = n0;

	/* Return immediately on empty needle */
	if (!l) return (void *)h;

	/* Return immediately when needle is longer than haystack */
	if (k<l) return 0;

	/* Use faster algorithms for short needles */
	h = memchr(h0, *n, k);
	if (!h || l==1) return (void *)h;
	k -= h - (const unsigned char *)h0;
	if (k<l) return 0;
	if (l==2) return twobyte_memmem(h, k, n);
	if (l==3) return threebyte_memmem(h, k, n);
	if (l==4) return fourbyte_memmem(h, k, n);

	return twoway_memmem(h, h+k, n, l);
}