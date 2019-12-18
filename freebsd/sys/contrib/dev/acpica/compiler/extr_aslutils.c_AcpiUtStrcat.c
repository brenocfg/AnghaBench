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
 scalar_t__ UtLocalCalloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

char *
AcpiUtStrcat (
    char                    *String1,
    char                    *String2)
{
    UINT32                  String1Length = strlen (String1);
    char                    *NewString = (char *) UtLocalCalloc (strlen (String1) + strlen (String2) + 1);

    strcpy (NewString, String1);
    strcpy (NewString + String1Length, String2);
    return (NewString);
}