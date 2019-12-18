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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Com_sprintf (char*,int,char*,float) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,float) ; 
 int strlen (char*) ; 

int WriteFloat(FILE *fp, float value)
{
	char buf[128];
	int l;

#ifdef BSPC
	snprintf(buf, sizeof(buf), "%f", value);
#else
	Com_sprintf(buf, sizeof(buf), "%f", value);
#endif
	l = strlen(buf);
	//strip any trailing zeros
	while(l-- > 1)
	{
		if (buf[l] != '0' && buf[l] != '.') break;
		if (buf[l] == '.')
		{
			buf[l] = 0;
			break;
		} //end if
		buf[l] = 0;
	} //end while
	//write the float to file
	if (fprintf(fp, "%s", buf) < 0) return 0;
	return 1;
}