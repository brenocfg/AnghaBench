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
typedef  int UINT64 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ AcpiUtStricmp (char*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  isprint (int) ; 
 int strlen (char*) ; 

__attribute__((used)) static BOOLEAN
CvIsFilename (
    char                    *Filename)
{
    UINT64                  Length = strlen(Filename);
    char                    *FileExt = Filename + Length - 4;
    UINT64                  i;


    if ((Length > 4) && AcpiUtStricmp (FileExt, ".dsl"))
    {
        return (FALSE);
    }

    for(i = 0; i<Length; ++i)
    {
        if (!isprint ((int) Filename[i]))
        {
            return (FALSE);
        }
    }

    return (TRUE);
}