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
 char* ACPI_COMMON_SIGNON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_OPTION (char*,char*) ; 
 int /*<<< orphan*/  ACPI_USAGE_HEADER (char*) ; 
 int /*<<< orphan*/  ASL_COMPILER_NAME ; 
 char* ASL_COMPLIANCE ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
Usage (
    void)
{
    printf (ACPI_COMMON_SIGNON (ASL_COMPILER_NAME));
    printf ("%s\n\n", ASL_COMPLIANCE);
    ACPI_USAGE_HEADER ("iasl [Options] [Files]");

    printf ("\nGeneral:\n");
    ACPI_OPTION ("-@  <file>",      "Specify command file");
    ACPI_OPTION ("-I  <dir>",       "Specify additional include directory");
    ACPI_OPTION ("-p  <prefix>",    "Specify path/filename prefix for all output files");
    ACPI_OPTION ("-v",              "Display compiler version");
    ACPI_OPTION ("-vo",             "Enable optimization comments");
    ACPI_OPTION ("-vs",             "Disable signon");

    printf ("\nHelp:\n");
    ACPI_OPTION ("-h",              "This message");
    ACPI_OPTION ("-hc",             "Display operators allowed in constant expressions");
    ACPI_OPTION ("-hd",             "Info for obtaining and disassembling binary ACPI tables");
    ACPI_OPTION ("-hf",             "Display help for output filename generation");
    ACPI_OPTION ("-hr",             "Display ACPI reserved method names");
    ACPI_OPTION ("-ht",             "Display currently supported ACPI table names");

    printf ("\nPreprocessor:\n");
    ACPI_OPTION ("-D <symbol>",     "Define symbol for preprocessor use");
    ACPI_OPTION ("-li",             "Create preprocessed output file (*.i)");
    ACPI_OPTION ("-P",              "Preprocess only and create preprocessor output file (*.i)");
    ACPI_OPTION ("-Pn",             "Disable preprocessor");

    printf ("\nErrors, Warnings, and Remarks:\n");
    ACPI_OPTION ("-va",             "Disable all errors/warnings/remarks");
    ACPI_OPTION ("-ve",             "Report only errors (ignore warnings and remarks)");
    ACPI_OPTION ("-vi",             "Less verbose errors and warnings for use with IDEs");
    ACPI_OPTION ("-vr",             "Disable remarks");
    ACPI_OPTION ("-vw <messageid>", "Ignore specific error, warning or remark");
    ACPI_OPTION ("-vx <messageid>", "Expect a specific warning, remark, or error");
    ACPI_OPTION ("-w <1|2|3>",      "Set warning reporting level");
    ACPI_OPTION ("-we",             "Report warnings as errors");
    ACPI_OPTION ("-ww <messageid>", "Report specific warning or remark as error");

    printf ("\nAML Bytecode Generation (*.aml):\n");
    ACPI_OPTION ("-oa",             "Disable all optimizations (compatibility mode)");
    ACPI_OPTION ("-of",             "Disable constant folding");
    ACPI_OPTION ("-oi",             "Disable integer optimization to Zero/One/Ones");
    ACPI_OPTION ("-on",             "Disable named reference string optimization");
    ACPI_OPTION ("-ot",             "Disable typechecking");
    ACPI_OPTION ("-cr",             "Disable Resource Descriptor error checking");
    ACPI_OPTION ("-in",             "Ignore NoOp operators");
    ACPI_OPTION ("-r <revision>",   "Override table header Revision (1-255)");

    printf ("\nListings:\n");
    ACPI_OPTION ("-l",              "Create mixed listing file (ASL source and AML) (*.lst)");
    ACPI_OPTION ("-lm",             "Create hardware summary map file (*.map)");
    ACPI_OPTION ("-ln",             "Create namespace file (*.nsp)");
    ACPI_OPTION ("-ls",             "Create combined source file (expanded includes) (*.src)");
    ACPI_OPTION ("-lx",             "Create cross-reference file (*.xrf)");

    printf ("\nFirmware Support - C Text Output:\n");
    ACPI_OPTION ("-tc",             "Create hex AML table in C (*.hex)");
    ACPI_OPTION ("-sc",             "Create named hex AML arrays in C (*.c)");
    ACPI_OPTION ("-ic",             "Create include file in C for -sc symbols (*.h)");
    ACPI_OPTION ("-so",             "Create namespace AML offset table in C (*.offset.h)");

    printf ("\nFirmware Support - Assembler Text Output:\n");
    ACPI_OPTION ("-ta",             "Create hex AML table in assembler (*.hex)");
    ACPI_OPTION ("-sa",             "Create named hex AML arrays in assembler (*.asm)");
    ACPI_OPTION ("-ia",             "Create include file in assembler for -sa symbols (*.inc)");

    printf ("\nFirmware Support - ASL Text Output:\n");
    ACPI_OPTION ("-ts",             "Create hex AML table in ASL (Buffer object) (*.hex)");

    printf ("\nLegacy-ASL to ASL+ Converter:\n");
    ACPI_OPTION ("-ca <file>",      "Convert legacy-ASL source file to new ASL+ file");
    ACPI_OPTION ("",                "  (Original comments are passed through to ASL+ file)");

    printf ("\nData Table Compiler:\n");
    ACPI_OPTION ("-tp",             "Compile tables with flex/bison prototype");
    ACPI_OPTION ("-G",              "Compile custom table that contains generic operators");
    ACPI_OPTION ("-T <sig list>|ALL",   "Create ACPI table template/example files");
    ACPI_OPTION ("-T <count>",      "Emit DSDT and <count> SSDTs to same file");
    ACPI_OPTION ("-vt",             "Create verbose template files (full disassembly)");

    printf ("\nAML Disassembler:\n");
    ACPI_OPTION ("-d  <f1 f2 ...>", "Disassemble or decode binary ACPI tables to file (*.dsl)");
    ACPI_OPTION ("",                "  (Optional, file type is automatically detected)");
    ACPI_OPTION ("-da <f1 f2 ...>", "Disassemble multiple tables from single namespace");
    ACPI_OPTION ("-db",             "Do not translate Buffers to Resource Templates");
    ACPI_OPTION ("-dc <f1 f2 ...>", "Disassemble AML and immediately compile it");
    ACPI_OPTION ("",                "  (Obtain DSDT from current system if no input file)");
    ACPI_OPTION ("-df",             "Force disassembler to assume table contains valid AML");
    ACPI_OPTION ("-dl",             "Emit legacy ASL code only (no C-style operators)");
    ACPI_OPTION ("-e  <f1 f2 ...>", "Include ACPI table(s) for external symbol resolution");
    ACPI_OPTION ("-fe <file>",      "Specify external symbol declaration file");
    ACPI_OPTION ("-in",             "Ignore NoOp opcodes");
    ACPI_OPTION ("-l",              "Disassemble to mixed ASL and AML code");
    ACPI_OPTION ("-vt",             "Dump binary table data in hex format within output file");

    printf ("\nDebug Options:\n");
    ACPI_OPTION ("-bc",             "Create converter debug file (*.cdb)");
    ACPI_OPTION ("-bf",             "Create debug file (full output) (*.txt)");
    ACPI_OPTION ("-bs",             "Create debug file (parse tree only) (*.txt)");
    ACPI_OPTION ("-bp <depth>",     "Prune ASL parse tree");
    ACPI_OPTION ("-bt <type>",      "Object type to be pruned from the parse tree");
    ACPI_OPTION ("-f",              "Ignore errors, force creation of AML output file(s)");
    ACPI_OPTION ("-m <size>",       "Set internal line buffer size (in Kbytes)");
    ACPI_OPTION ("-n",              "Parse only, no output generation");
    ACPI_OPTION ("-oc",             "Display compile times and statistics");
    ACPI_OPTION ("-x <level>",      "Set debug level for trace output");
    ACPI_OPTION ("-z",              "Do not insert new compiler ID for DataTables");
}