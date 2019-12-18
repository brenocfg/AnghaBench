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
typedef  size_t u_int ;
typedef  size_t u_char ;

/* Variables and functions */
 size_t NLOCK_FIELDS ; 
 size_t SHA512_DIGEST_LENGTH ; 

__attribute__((used)) static void
g_bde_shuffle_lock(u_char *sha2, int *buf)
{
	int j, k, l;
	u_int u;

	/* Assign the fields sequential positions */
	for(u = 0; u < NLOCK_FIELDS; u++)
		buf[u] = u;

	/* Then mix it all up */
	for(u = 48; u < SHA512_DIGEST_LENGTH; u++) {
		j = sha2[u] % NLOCK_FIELDS;
		k = (sha2[u] / NLOCK_FIELDS) % NLOCK_FIELDS;
		l = buf[j];
		buf[j] = buf[k];
		buf[k] = l;
	}
}