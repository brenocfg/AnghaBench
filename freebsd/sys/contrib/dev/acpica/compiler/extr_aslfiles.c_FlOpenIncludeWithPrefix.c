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
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ASL_EOF ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_MSG_INCLUDE_FILE ; 
 int /*<<< orphan*/  ASL_PARSE_OUTPUT ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 char* AslGbl_CurrentLineBuffer ; 
 scalar_t__ AslGbl_CurrentLineNumber ; 
 int /*<<< orphan*/  AslPushInputFileStack (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  DT_ALLOW_MULTILINE_QUOTES ; 
 int /*<<< orphan*/  DbgPrint (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ DtGetNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* FlMergePathnames (char*,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE *
FlOpenIncludeWithPrefix (
    char                    *PrefixDir,
    ACPI_PARSE_OBJECT       *Op,
    char                    *Filename)
{
    FILE                    *IncludeFile;
    char                    *Pathname;
    UINT32                  OriginalLineNumber;


    /* Build the full pathname to the file */

    Pathname = FlMergePathnames (PrefixDir, Filename);

    DbgPrint (ASL_PARSE_OUTPUT, "Include: Opening file - \"%s\"\n\n",
        Pathname);

    /* Attempt to open the file, push if successful */

    IncludeFile = fopen (Pathname, "r");
    if (!IncludeFile)
    {
        return (NULL);
    }

    /*
     * Check the entire include file for any # preprocessor directives.
     * This is because there may be some confusion between the #include
     * preprocessor directive and the ASL Include statement. A file included
     * by the ASL include cannot contain preprocessor directives because
     * the preprocessor has already run by the time the ASL include is
     * recognized (by the compiler, not the preprocessor.)
     *
     * Note: DtGetNextLine strips/ignores comments.
     * Save current line number since DtGetNextLine modifies it.
     */
    AslGbl_CurrentLineNumber--;
    OriginalLineNumber = AslGbl_CurrentLineNumber;

    while (DtGetNextLine (IncludeFile, DT_ALLOW_MULTILINE_QUOTES) != ASL_EOF)
    {
        if (AslGbl_CurrentLineBuffer[0] == '#')
        {
            AslError (ASL_ERROR, ASL_MSG_INCLUDE_FILE,
                Op, "use #include instead");
        }
    }

    AslGbl_CurrentLineNumber = OriginalLineNumber;

    /* Must seek back to the start of the file */

    fseek (IncludeFile, 0, SEEK_SET);

    /* Push the include file on the open input file stack */

    AslPushInputFileStack (IncludeFile, Pathname);
    return (IncludeFile);
}