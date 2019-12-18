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
typedef  long uLong ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * prga; int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 unsigned char* Z_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 long crc32 (long,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ prgainfo ; 

void wepify(unsigned char* body, int dlen) {
	uLong crc;
	unsigned long *pcrc;
	int i;
	
	assert(dlen + 4 <= prgainfo.len);

	// iv
	memcpy(body, prgainfo.iv, 3);
	body +=3;
	*body++ = 0;

	// crc
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, body, dlen);
	pcrc = (unsigned long*) (body+dlen);
	*pcrc = crc;

	for (i = 0; i < dlen +4; i++)
		*body++ ^= prgainfo.prga[i];
}