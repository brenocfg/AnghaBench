#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* hv; } ;
typedef  TYPE_1__ sha1_digest ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,unsigned long*,unsigned long*,unsigned long*,unsigned long*,unsigned long*,int*) ; 

__attribute__((used)) static int/*BOOL*/
do_leap_hash(
	sha1_digest * mac,
	char const  * cp )
{
	int wi, di, num, len;
	unsigned long tmp[5];

	memset(mac, 0, sizeof(*mac));
	num = sscanf(cp, " %lx %lx %lx %lx %lx%n",
		     &tmp[0], &tmp[1], &tmp[2], &tmp[3], &tmp[4],
		     &len);
	if (num != 5 || cp[len] > ' ')
		return FALSE;

	/* now do the byte twiddle */
	for (wi=0; wi < 5; ++wi)
		for (di=3; di >= 0; --di) {
			mac->hv[wi*4 + di] =
				(unsigned char)(tmp[wi] & 0x0FF);
			tmp[wi] >>= 8;
		}
	return TRUE;
}