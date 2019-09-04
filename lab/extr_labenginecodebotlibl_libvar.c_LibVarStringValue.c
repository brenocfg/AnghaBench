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

float LibVarStringValue(const char *string)
{
	int dotfound = 0;
	float value = 0;

	while(*string)
	{
		if (*string < '0' || *string > '9')
		{
			if (dotfound || *string != '.')
			{
				return 0;
			} //end if
			else
			{
				dotfound = 10;
				string++;
			} //end if
		} //end if
		if (dotfound)
		{
			value = value + (float) (*string - '0') / (float) dotfound;
			dotfound *= 10;
		} //end if
		else
		{
			value = value * 10.0 + (float) (*string - '0');
		} //end else
		string++;
	} //end while
	return value;
}