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
typedef  long uLong ;
struct ieee80211_frame {int dummy; } ;
typedef  int /*<<< orphan*/  seed ;
typedef  int /*<<< orphan*/  RC4_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,char*,char*) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int,char*) ; 
 char* Z_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 long crc32 (long,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

int wep_decrypt(struct ieee80211_frame *wh, int len, char *key, int klen)
{
	RC4_KEY k;
	char seed[64];
	char *p = (char*) (wh+1);
	uLong crc = crc32(0L, Z_NULL, 0);
	uLong *pcrc;

	assert(sizeof(seed) >= klen + 3);
	memcpy(seed, p, 3);
	memcpy(&seed[3], key, klen);

	RC4_set_key(&k, klen+3, seed);
	
	len -= sizeof(*wh);
	len -= 4;
	p += 4;
	RC4(&k, len, p, p);

	crc = crc32(crc, p, len - 4);
	pcrc = (uLong*) (p+len-4);

	if (*pcrc == crc)
		return 0;

	return -1;
}