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
typedef  int /*<<< orphan*/  krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static krb5_error_code
rr13(unsigned char *buf, size_t len)
{
    unsigned char *tmp;
    int bytes = (len + 7) / 8;
    int i;
    if(len == 0)
	return 0;
    {
	const int bits = 13 % len;
	const int lbit = len % 8;

	tmp = malloc(bytes);
	if (tmp == NULL)
	    return ENOMEM;
	memcpy(tmp, buf, bytes);
	if(lbit) {
	    /* pad final byte with inital bits */
	    tmp[bytes - 1] &= 0xff << (8 - lbit);
	    for(i = lbit; i < 8; i += len)
		tmp[bytes - 1] |= buf[0] >> i;
	}
	for(i = 0; i < bytes; i++) {
	    int bb;
	    int b1, s1, b2, s2;
	    /* calculate first bit position of this byte */
	    bb = 8 * i - bits;
	    while(bb < 0)
		bb += len;
	    /* byte offset and shift count */
	    b1 = bb / 8;
	    s1 = bb % 8;

	    if(bb + 8 > bytes * 8)
		/* watch for wraparound */
		s2 = (len + 8 - s1) % 8;
	    else
		s2 = 8 - s1;
	    b2 = (b1 + 1) % bytes;
	    buf[i] = (tmp[b1] << s1) | (tmp[b2] >> s2);
	}
	free(tmp);
    }
    return 0;
}