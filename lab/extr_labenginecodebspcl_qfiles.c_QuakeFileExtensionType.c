#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; scalar_t__ extension; } ;

/* Variables and functions */
 int QFILETYPE_UNKNOWN ; 
 TYPE_1__* quakefiletypes ; 
 int /*<<< orphan*/  stricmp (char*,scalar_t__) ; 

int QuakeFileExtensionType(char *extension)
{
	int i;

	for (i = 0; quakefiletypes[i].extension; i++)
	{
		if (!stricmp(extension, quakefiletypes[i].extension))
		{
			return quakefiletypes[i].type;
		} //end if
	} //end for
	return QFILETYPE_UNKNOWN;
}