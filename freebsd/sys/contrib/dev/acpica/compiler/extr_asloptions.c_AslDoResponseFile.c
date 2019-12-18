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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASL_STRING_BUFFER_SIZE ; 
 int AcpiGbl_Opterr ; 
 int AcpiGbl_Optind ; 
 int AslDoOptions (int,char**,int /*<<< orphan*/ ) ; 
 char* AslGbl_StringBuffer ; 
 char* AslGbl_StringBuffer2 ; 
 int /*<<< orphan*/  AslMergeOptionTokens (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
AslDoResponseFile (
    char                    *Filename)
{
    char                    *argv = AslGbl_StringBuffer2;
    FILE                    *ResponseFile;
    int                     OptStatus = 0;
    int                     Opterr;
    int                     Optind;


    ResponseFile = fopen (Filename, "r");
    if (!ResponseFile)
    {
        printf ("Could not open command file %s, %s\n",
            Filename, strerror (errno));
        return (-1);
    }

    /* Must save the current GetOpt globals */

    Opterr = AcpiGbl_Opterr;
    Optind = AcpiGbl_Optind;

    /*
     * Process all lines in the response file. There must be one complete
     * option per line
     */
    while (fgets (AslGbl_StringBuffer, ASL_STRING_BUFFER_SIZE, ResponseFile))
    {
        /* Compress all tokens, allowing us to use a single argv entry */

        AslMergeOptionTokens (AslGbl_StringBuffer, AslGbl_StringBuffer2);

        /* Process the option */

        AcpiGbl_Opterr = 0;
        AcpiGbl_Optind = 0;

        OptStatus = AslDoOptions (1, &argv, TRUE);
        if (OptStatus)
        {
            printf ("Invalid option in command file %s: %s\n",
                Filename, AslGbl_StringBuffer);
            break;
        }
    }

    /* Restore the GetOpt globals */

    AcpiGbl_Opterr = Opterr;
    AcpiGbl_Optind = Optind;

    fclose (ResponseFile);
    return (OptStatus);
}