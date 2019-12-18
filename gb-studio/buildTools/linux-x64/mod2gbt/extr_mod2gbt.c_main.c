#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int* name; int* pattern_table; int song_length; int /*<<< orphan*/ * pattern; int /*<<< orphan*/  identifier; } ;
typedef  TYPE_1__ mod_file_t ;

/* Variables and functions */
 int DEFAULT_ROM_BANK ; 
 int /*<<< orphan*/  convert_pattern (int /*<<< orphan*/ *,int) ; 
 int current_output_bank ; 
 char* label_name ; 
 TYPE_1__* load_file (char*) ; 
 int /*<<< orphan*/  out_close () ; 
 int /*<<< orphan*/  out_open () ; 
 int /*<<< orphan*/  out_write_dec (int) ; 
 int /*<<< orphan*/  out_write_str (char*) ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int main(int argc, char *argv[])
{
    int i;

    printf("mod2gbt v2.2 (part of GBT Player)\n");
    printf("Copyright (c) 2009-2018 Antonio Niño Díaz "
           "<antonio_nd@outlook.com>\n");
    printf("All rights reserved\n");
    printf("\n");

    if ((argc < 3) || (argc > 4))
    {
        print_usage();
        return -1;
    }

    strcpy(label_name, argv[2]);

    current_output_bank = DEFAULT_ROM_BANK;

    if (argc == 4)
    {
        if (sscanf(argv[3], "%d", &current_output_bank) != 1)
        {
            printf("Invalid bank: '%s'\n\n", argv[4]);
            print_usage();
            return -2;
        }
        else
        {
            printf("Output to bank: %d\n", current_output_bank);
        }
    }

    mod_file_t *modfile = load_file(argv[1]);

    if (modfile == NULL)
        return -2;

    printf("%s loaded!\n", argv[1]);

    if (strncmp(modfile->identifier, "M.K.", 4) == 0)
    {
        printf("Valid mod file!\n");
    }
    else
    {
        printf("ERROR: Not a valid mod file.\n"
               "Only 4 channel mod files with 31 samples allowed.\n");
        return -3;
    }

    printf("\nSong name: ");
    for (i = 0; i < 20; i++)
        if (modfile->name[i])
            printf("%c", modfile->name[i]);
    printf("\n");

    u8 num_patterns = 0;

    for (i = 0; i < 128; i++)
        if (modfile->pattern_table[i] > num_patterns)
            num_patterns = modfile->pattern_table[i];

    num_patterns++;

    printf("Number of patterns: %d\n", num_patterns);

    out_open();

    out_write_str("\n// File created by mod2gbt\n\n");

    out_write_str("#pragma bank=");
    out_write_dec(current_output_bank);
    out_write_str("\n\n");

    printf("\nConverting patterns...\n");
    for (i = 0; i < num_patterns; i++)
    {
        printf(".");
        convert_pattern(&(modfile->pattern[i]), i);
    }

    printf("\n\nPattern order...\n");

    out_write_str("const unsigned char * const");
    out_write_str(label_name);
    out_write_str("_Data[] = {\n");

    for (i = 0; i < modfile->song_length; i++)
    {
        out_write_str("    ");
        out_write_str(label_name);
        out_write_dec(modfile->pattern_table[i]);
        out_write_str(",\n");
    }

    out_write_str("    0x0000\n");
    out_write_str("};\n\n");

    out_close();

    printf("\nDone!\n");

    return 0;
}