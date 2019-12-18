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
 int strlen (char const*) ; 

__attribute__((used)) static int extract_string(const char *src, char *dest, int len)
{
	int pos = 0;
	int esc = 0;
	int off = -1;

	for( pos = 0; (pos < strlen(src)) && (pos < len); pos++ )
	{
		if( (off == -1) && (src[pos] == '"') )
		{
			off = pos + 1;
		}
		else if( off >= 0 )
		{
			if( esc == 1 )
			{
				switch (src[pos])
				{
				case '"':
				case '\\':
					off++;
					break;
				}
				dest[pos-off] = src[pos];
				esc = 0;
			}
			else if( src[pos] == '\\' )
			{
				dest[pos-off] = src[pos];
				esc = 1;
			}
			else if( src[pos] != '"' )
			{
				dest[pos-off] = src[pos];
			}
			else
			{
				dest[pos-off] = '\0';
				break;
			}
		}
	}

	return (off > -1) ? strlen(dest) : -1;
}