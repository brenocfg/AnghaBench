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
struct TYPE_2__ {int rawsz; } ;

/* Variables and functions */
 int hex2chr (char const*) ; 
 TYPE_1__* the_hash_algo ; 

int get_sha1_hex(const char *hex, unsigned char *sha1)
{
	int i;
	for (i = 0; i < the_hash_algo->rawsz; i++) {
		int val = hex2chr(hex);
		if (val < 0)
			return -1;
		*sha1++ = val;
		hex += 2;
	}
	return 0;
}