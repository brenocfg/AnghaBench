#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_10__ {char* TableSignature; char* TableId; } ;
struct TYPE_7__ {char* String; scalar_t__* Buffer; } ;
struct TYPE_8__ {void* ParseOpcode; TYPE_3__* Next; TYPE_1__ Value; int /*<<< orphan*/  Filename; TYPE_3__* Child; } ;
struct TYPE_9__ {TYPE_2__ Asl; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_SIZE ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_NAMESEG_SIZE ; 
 scalar_t__ ACPI_OEM_ID_SIZE ; 
 int ACPI_OEM_TABLE_ID_SIZE ; 
 int /*<<< orphan*/  ASL_ERROR ; 
 int /*<<< orphan*/  ASL_FILE_AML_OUTPUT ; 
 int /*<<< orphan*/  ASL_MSG_OEM_ID ; 
 int /*<<< orphan*/  ASL_MSG_OEM_TABLE_ID ; 
 int /*<<< orphan*/  ASL_MSG_OUTPUT_FILE_OPEN ; 
 int /*<<< orphan*/  ASL_MSG_TABLE_SIGNATURE ; 
 int /*<<< orphan*/  AslError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 char* AslGbl_DirectoryPath ; 
 TYPE_5__* AslGbl_FilesList ; 
 char* AslGbl_OutputFilenamePrefix ; 
 char* AslGbl_TableId ; 
 char* AslGbl_TableSignature ; 
 scalar_t__ AslGbl_UseDefaultAmlFilename ; 
 int /*<<< orphan*/  FlCloseFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlDeleteFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FlOpenAmlOutputFile (char*) ; 
 int /*<<< orphan*/  FlSwitchFileSet (int /*<<< orphan*/ ) ; 
 void* PARSEOP_DEFAULT_ARG ; 
 int /*<<< orphan*/  UtConvertBackslashes (char*) ; 
 char* UtLocalCacheCalloc (int) ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
OpnDoDefinitionBlock (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *Child;
    ACPI_SIZE               Length;
    UINT32                  i;
    char                    *Filename;
    ACPI_STATUS             Status;


    /*
     * These nodes get stuffed into the table header. They are special
     * cased when the table is written to the output file.
     *
     * Mark all of these nodes as non-usable so they won't get output
     * as AML opcodes!
     */

    /* Get AML filename. Use it if non-null */

    Child = Op->Asl.Child;
    if (Child->Asl.Value.Buffer  &&
        *Child->Asl.Value.Buffer &&
        (AslGbl_UseDefaultAmlFilename))
    {
        /*
         * The walk may traverse multiple definition blocks. Switch files
         * to ensure that the correct files are manipulated.
         */
        FlSwitchFileSet (Op->Asl.Filename);

        /*
         * We will use the AML filename that is embedded in the source file
         * for the output filename.
         */
        Filename = UtLocalCacheCalloc (strlen (AslGbl_DirectoryPath) +
            strlen ((char *) Child->Asl.Value.Buffer) + 1);

        /* Prepend the current directory path */

        strcpy (Filename, AslGbl_DirectoryPath);
        strcat (Filename, (char *) Child->Asl.Value.Buffer);

        AslGbl_OutputFilenamePrefix = Filename;
        UtConvertBackslashes (AslGbl_OutputFilenamePrefix);

        /*
         * Use the definition block file parameter instead of the input
         * filename. Since all files were opened previously, remove the
         * existing file and open a new file with the name of this
         * definiton block parameter. Since AML code generation has yet
         * to happen, the previous file can be removed without any impacts.
         */
        FlCloseFile (ASL_FILE_AML_OUTPUT);
        FlDeleteFile (ASL_FILE_AML_OUTPUT);
        Status = FlOpenAmlOutputFile (AslGbl_OutputFilenamePrefix);
        if (ACPI_FAILURE (Status))
        {
            AslError (ASL_ERROR, ASL_MSG_OUTPUT_FILE_OPEN, NULL, NULL);
            return;
        }
    }

    Child->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;

    /* Signature */

    Child = Child->Asl.Next;
    Child->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
    if (Child->Asl.Value.String)
    {
        AslGbl_FilesList->TableSignature = Child->Asl.Value.String;
        AslGbl_TableSignature = Child->Asl.Value.String;
        if (strlen (AslGbl_TableSignature) != ACPI_NAMESEG_SIZE)
        {
            AslError (ASL_ERROR, ASL_MSG_TABLE_SIGNATURE, Child,
                "Length must be exactly 4 characters");
        }

        for (i = 0; i < ACPI_NAMESEG_SIZE; i++)
        {
            if (!isalnum ((int) AslGbl_TableSignature[i]))
            {
                AslError (ASL_ERROR, ASL_MSG_TABLE_SIGNATURE, Child,
                    "Contains non-alphanumeric characters");
            }
        }
    }

    /* Revision */

    Child = Child->Asl.Next;
    Child->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;

    /*
     * We used the revision to set the integer width earlier
     */

    /* OEMID */

    Child = Child->Asl.Next;
    Child->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
    if (Child->Asl.Value.String &&
        strlen (Child->Asl.Value.String) > ACPI_OEM_ID_SIZE)
    {
        AslError (ASL_ERROR, ASL_MSG_OEM_ID, Child,
            "Length cannot exceed 6 characters");
    }

    /* OEM TableID */

    Child = Child->Asl.Next;
    Child->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
    if (Child->Asl.Value.String)
    {
        Length = strlen (Child->Asl.Value.String);
        if (Length > ACPI_OEM_TABLE_ID_SIZE)
        {
            AslError (ASL_ERROR, ASL_MSG_OEM_TABLE_ID, Child,
                "Length cannot exceed 8 characters");
        }

        AslGbl_TableId = UtLocalCacheCalloc (Length + 1);
        strcpy (AslGbl_TableId, Child->Asl.Value.String);
        AslGbl_FilesList->TableId = AslGbl_TableId;

        /*
         * Convert anything non-alphanumeric to an underscore. This
         * allows us to use the TableID to generate unique C symbols.
         */
        for (i = 0; i < Length; i++)
        {
            if (!isalnum ((int) AslGbl_TableId[i]))
            {
                AslGbl_TableId[i] = '_';
            }
        }
    }

    /* OEM Revision */

    Child = Child->Asl.Next;
    Child->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;
}