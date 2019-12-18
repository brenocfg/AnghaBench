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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  FSEv06_DTable ;

/* Variables and functions */
 int FSEv06_DTABLE_SIZE_U32 (unsigned int) ; 
 unsigned int FSEv06_TABLELOG_ABSOLUTE_MAX ; 
 scalar_t__ malloc (int) ; 

FSEv06_DTable* FSEv06_createDTable (unsigned tableLog)
{
    if (tableLog > FSEv06_TABLELOG_ABSOLUTE_MAX) tableLog = FSEv06_TABLELOG_ABSOLUTE_MAX;
    return (FSEv06_DTable*)malloc( FSEv06_DTABLE_SIZE_U32(tableLog) * sizeof (U32) );
}