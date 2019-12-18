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
 int /*<<< orphan*/  le16_to_cpu (unsigned int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,unsigned long) ; 

void outsw (unsigned long port, const void *src, unsigned long count)
{
	unsigned int l = 0, l2;
	const unsigned char *p;

	p = (const unsigned char *)src;
	
	if (!count)
		return;
	
	switch (((unsigned long)p) & 0x3)
	{
	 case 0x00:			/* Buffer 32-bit aligned */
		while (count>=2) {
			count -= 2;
			l = *(unsigned int *)p;
			p += 4;
			outw(le16_to_cpu(l >> 16), port);
			outw(le16_to_cpu(l & 0xffff), port);
		}
		if (count) {
			outw(le16_to_cpu(*(unsigned short*)p), port);
		}
		break;
	
	 case 0x02:			/* Buffer 16-bit aligned */
		
		outw(le16_to_cpu(*(unsigned short*)p), port);
		p += 2;
		count--;
		
		while (count>=2) {
			count -= 2;
			l = *(unsigned int *)p;
			p += 4;
			outw(le16_to_cpu(l >> 16), port);
			outw(le16_to_cpu(l & 0xffff), port);
		}
		if (count) {
			outw(le16_to_cpu(*(unsigned short *)p), port);
		}
		break;
		
	 case 0x01:			/* Buffer 8-bit aligned */	
		/* I don't bother with 32bit transfers
		 * in this case, 16bit will have to do -- DE */
		
		l  = *p << 8;
		p++;
		count--;
		while (count)
		{
			count--;
			l2 = *(unsigned short *)p;
			p += 2;
			outw(le16_to_cpu(l | l2 >> 8), port);
		        l = l2 << 8;
		}
		l2 = *(unsigned char *)p;
		outw (le16_to_cpu(l | l2>>8), port);
		break;
	
	}
}