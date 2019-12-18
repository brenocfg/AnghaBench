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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int fgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 

BOOLEAN
UtQueryForOverwrite (
    char                    *Pathname)
{
    struct stat             StatInfo;
    int                     InChar;


    if (!stat (Pathname, &StatInfo))
    {
        fprintf (stderr, "Target file \"%s\" already exists, overwrite? [y|n] ",
            Pathname);

        InChar = fgetc (stdin);
        if (InChar == '\n')
        {
            InChar = fgetc (stdin);
        }

        if ((InChar != 'y') && (InChar != 'Y'))
        {
            return (FALSE);
        }
    }

    return (TRUE);
}