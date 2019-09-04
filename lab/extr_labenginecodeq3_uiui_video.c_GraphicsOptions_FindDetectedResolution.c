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
 int /*<<< orphan*/  Q_stricmp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * builtinResolutions ; 
 scalar_t__* detectedResolutions ; 
 int /*<<< orphan*/  resolutionsDetected ; 

__attribute__((used)) static int GraphicsOptions_FindDetectedResolution( int mode )
{
	int i;

	if( !resolutionsDetected )
		return mode;

	if( mode < 0 )
		return -1;

	for( i = 0; detectedResolutions[ i ]; i++ )
	{
		if( !Q_stricmp( builtinResolutions[ mode ], detectedResolutions[ i ] ) )
			return i;
	}

	return -1;
}