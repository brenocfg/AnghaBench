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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  reverse_endian32 (int) ; 

uint32_t get_buffer_crc ( char* filebuffer,size_t size )
{

	long crc=0xffffffffL;
	long crcxor = 0xffffffffL;
	long num4 = 0xffffffffL;
	long num5 = size;
	long num6 = 0x4c11db7L;
	long num7 = 0x80000000L;
	int i;
	long j;
	for ( i = 0; i < ( num5 ); i++ )
	{
		long num2 = filebuffer[i];
		for ( j = 0x80L; j != 0L; j = j >> 1 )
		{
			long num3 = crc & num7;
			crc = crc << 1;
			if ( ( num2 & j ) != 0L )
			{
				num3 ^= num7;
			}
			if ( num3 != 0L )
			{
				crc ^= num6;
			}
		}
	}
	crc ^= crcxor;
	crc &= num4;

	uint8_t b1 = ( uint8_t ) ( ( crc & -16777216L ) >> 0x18 );
	uint8_t b2 = ( uint8_t ) ( ( crc & 0xff0000L ) >> 0x10 );
	uint8_t b3 = ( uint8_t ) ( ( crc & 0xff00L ) >> 8 );
	uint8_t b4 = ( uint8_t ) ( crc & 0xffL );
	int32_t crc_result = ( b1 | b2 << 8| b3 << 16| b4 <<24 );
	return reverse_endian32 ( crc_result );
}