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
typedef  int BN_ULONG ;

/* Variables and functions */

int BN_num_bits_word(BN_ULONG l)
	{
	static const char bits[256]={
		0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,
		5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
		6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
		6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
		};

#if defined(SIXTY_FOUR_BIT_LONG)
	if (l & 0xffffffff00000000L)
		{
		if (l & 0xffff000000000000L)
			{
			if (l & 0xff00000000000000L)
				{
				return(bits[(int)(l>>56)]+56);
				}
			else    return(bits[(int)(l>>48)]+48);
			}
		else
			{
			if (l & 0x0000ff0000000000L)
				{
				return(bits[(int)(l>>40)]+40);
				}
			else    return(bits[(int)(l>>32)]+32);
			}
		}
	else
#else
#ifdef SIXTY_FOUR_BIT
	if (l & 0xffffffff00000000LL)
		{
		if (l & 0xffff000000000000LL)
			{
			if (l & 0xff00000000000000LL)
				{
				return(bits[(int)(l>>56)]+56);
				}
			else    return(bits[(int)(l>>48)]+48);
			}
		else
			{
			if (l & 0x0000ff0000000000LL)
				{
				return(bits[(int)(l>>40)]+40);
				}
			else    return(bits[(int)(l>>32)]+32);
			}
		}
	else
#endif
#endif
		{
#if defined(THIRTY_TWO_BIT) || defined(SIXTY_FOUR_BIT) || defined(SIXTY_FOUR_BIT_LONG)
		if (l & 0xffff0000L)
			{
			if (l & 0xff000000L)
				return(bits[(int)(l>>24L)]+24);
			else    return(bits[(int)(l>>16L)]+16);
			}
		else
#endif
			{
#if defined(SIXTEEN_BIT) || defined(THIRTY_TWO_BIT) || defined(SIXTY_FOUR_BIT) || defined(SIXTY_FOUR_BIT_LONG)
			if (l & 0xff00L)
				return(bits[(int)(l>>8)]+8);
			else
#endif
				return(bits[(int)(l   )]  );
			}
		}
	}