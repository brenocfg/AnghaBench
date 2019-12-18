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
typedef  int UINT32 ;

/* Variables and functions */
 char* UtLocalCacheCalloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

char *
CvAppendInlineComment (
    char                    *InlineComment,
    char                    *ToAdd)
{
    char*                   Str;
    UINT32                  Size = 0;


    if (!InlineComment)
    {
        return (ToAdd);
    }

    if (!ToAdd)
    {
        return (InlineComment);
    }

    Size = strlen (ToAdd);
    Size += strlen (InlineComment);
    Str = UtLocalCacheCalloc (Size + 1);

    strcpy (Str, InlineComment);
    strcat (Str, ToAdd);
    Str[Size +1] = 0;
    return (Str);
}