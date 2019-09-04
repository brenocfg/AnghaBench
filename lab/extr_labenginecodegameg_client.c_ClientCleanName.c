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
 scalar_t__ ColorIndex (char const) ; 
 char Q_COLOR_ESCAPE ; 
 scalar_t__ Q_IsColorString (char*) ; 
 int /*<<< orphan*/  Q_strncpyz (char*,char*,int) ; 

__attribute__((used)) static void ClientCleanName(const char *in, char *out, int outSize)
{
	int outpos = 0, colorlessLen = 0, spaces = 0;

	// discard leading spaces
	for(; *in == ' '; in++);
	
	for(; *in && outpos < outSize - 1; in++)
	{
		out[outpos] = *in;

		if(*in == ' ')
		{
			// don't allow too many consecutive spaces
			if(spaces > 2)
				continue;
			
			spaces++;
		}
		else if(outpos > 0 && out[outpos - 1] == Q_COLOR_ESCAPE)
		{
			if(Q_IsColorString(&out[outpos - 1]))
			{
				colorlessLen--;
				
				if(ColorIndex(*in) == 0)
				{
					// Disallow color black in names to prevent players
					// from getting advantage playing in front of black backgrounds
					outpos--;
					continue;
				}
			}
			else
			{
				spaces = 0;
				colorlessLen++;
			}
		}
		else
		{
			spaces = 0;
			colorlessLen++;
		}
		
		outpos++;
	}

	out[outpos] = '\0';

	// don't allow empty names
	if( *out == '\0' || colorlessLen == 0)
		Q_strncpyz(out, "UnnamedPlayer", outSize );
}