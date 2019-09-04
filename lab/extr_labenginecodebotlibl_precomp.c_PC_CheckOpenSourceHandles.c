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
 int MAX_SOURCEFILES ; 
 scalar_t__* sourceFiles ; 

void PC_CheckOpenSourceHandles(void)
{
	int i;

	for (i = 1; i < MAX_SOURCEFILES; i++)
	{
		if (sourceFiles[i])
		{
#ifdef BOTLIB
			botimport.Print(PRT_ERROR, "file %s still open in precompiler\n", sourceFiles[i]->scriptstack->filename);
#endif	//BOTLIB
		} //end if
	} //end for
}