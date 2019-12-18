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
 unsigned int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (unsigned long) ; 

void insw (unsigned long port, void *dst, unsigned long count)
{
	unsigned int l = 0, l2;
	unsigned char *p;

	p = (unsigned char *)dst;
	
	if (!count)
		return;
	
	switch (((unsigned long)p) & 0x3)
	{
	 case 0x00:			/* Buffer 32-bit aligned */
		while (count>=2) {
			
			count -= 2;
			l = cpu_to_le16(inw(port)) << 16;
			l |= cpu_to_le16(inw(port));
			*(unsigned int *)p = l;
			p += 4;
		}
		if (count) {
			*(unsigned short *)p = cpu_to_le16(inw(port));
		}
		break;
	
	 case 0x02:			/* Buffer 16-bit aligned */
		*(unsigned short *)p = cpu_to_le16(inw(port));
		p += 2;
		count--;
		while (count>=2) {
			
			count -= 2;
			l = cpu_to_le16(inw(port)) << 16;
			l |= cpu_to_le16(inw(port));
			*(unsigned int *)p = l;
			p += 4;
		}
		if (count) {
			*(unsigned short *)p = cpu_to_le16(inw(port));
		}
		break;
		
	 case 0x01:			/* Buffer 8-bit aligned */
	 case 0x03:
		/* I don't bother with 32bit transfers
		 * in this case, 16bit will have to do -- DE */
		--count;
		
		l = cpu_to_le16(inw(port));
		*p = l >> 8;
		p++;
		while (count--)
		{
			l2 = cpu_to_le16(inw(port));
			*(unsigned short *)p = (l & 0xff) << 8 | (l2 >> 8);
			p += 2;
			l = l2;
		}
		*p = l & 0xff;
		break;
	}
}