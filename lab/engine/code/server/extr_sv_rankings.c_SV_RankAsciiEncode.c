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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* s_ascii_encoding ; 

__attribute__((used)) static int SV_RankAsciiEncode( char* dest, const unsigned char* src, 
	int src_len )
{
	unsigned char	bin[3];
	unsigned char	txt[4];
	int				dest_len = 0;
	int				i;
	int				j;
	int				num_chars;

	assert( dest != NULL );
	assert( src != NULL );
	
	for( i = 0; i < src_len; i += 3 )
	{
		// read three bytes of input
		for( j = 0; j < 3; j++ )
		{
			bin[j] = (i + j < src_len) ? src[i + j] : 0;
		}

		// get four 6-bit values from three bytes
		txt[0] = bin[0] >> 2;
		txt[1] = ((bin[0] << 4) | (bin[1] >> 4)) & 63;
		txt[2] = ((bin[1] << 2) | (bin[2] >> 6)) & 63;
		txt[3] = bin[2] & 63;

		// store ASCII encoding of 6-bit values
		num_chars = (i + 2 < src_len) ? 4 : ((src_len - i) * 4) / 3 + 1;
		for( j = 0; j < num_chars; j++ )
		{
			dest[dest_len++] = s_ascii_encoding[txt[j]];
		}
	}
	
	dest[dest_len] = '\0';

	return dest_len;
}