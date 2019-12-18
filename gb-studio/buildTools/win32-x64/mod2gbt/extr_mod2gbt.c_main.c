#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int* name; int* pattern_table; int song_lenght; int /*<<< orphan*/ * pattern; TYPE_1__* sample; int /*<<< orphan*/  identifier; } ;
typedef  TYPE_2__ mod_file_t ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int DEFAULT_ROM_BANK ; 
 int /*<<< orphan*/  convert_pattern (int /*<<< orphan*/ *,int) ; 
 int current_output_bank ; 
 char* label_name ; 
 TYPE_2__* load_file (char*) ; 
 int /*<<< orphan*/  out_close () ; 
 int /*<<< orphan*/  out_open () ; 
 int /*<<< orphan*/  out_write_dec (int) ; 
 int /*<<< orphan*/  out_write_str (char*,char*) ; 
 int output_asm ; 
 int /*<<< orphan*/  print_usage () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

int main(int argc, char * argv[])
{
    printf("     +-------------------------------------------+\n");
    printf("     |                                           |\n");
    printf("     |     mod2gbt v2.0 (part of GBT Player)     |\n");
    printf("     |                                           |\n");
    printf("     |                                           |\n");
    printf("     | Copyright (C) 2009-2014 Antonio Nino Diaz |\n");
    printf("     |                      All rights reserved. |\n");
    printf("     |                                           |\n");
	printf("     |                   antonio_nd@outlook.com  |\n");
    printf("     |                                           |\n");
    printf("     +-------------------------------------------+\n");

    printf("\n");

    if( (argc != 4) && (argc != 5))
    {
        print_usage();
        return -1;
    }

    strcpy(label_name,argv[2]);

    if(strcmp(argv[3],"-a") == 0)
    {
        output_asm = 1;
    }
    else if(strcmp(argv[3],"-c") == 0)
    {
        output_asm = 0;
    }
    else
    {
        print_usage();
        return -1;
    }

    current_output_bank = DEFAULT_ROM_BANK;

    if(argc == 5)
    {
        if(sscanf(argv[4],"%d",&current_output_bank) != 1)
        {
            printf("Invalid bank: %s\n\n",argv[4]);
            print_usage();
            return -2;
        }
        else
        {
            printf("Output to bank: %d\n",current_output_bank);
        }
    }

    int i;
    mod_file_t * modfile = load_file(argv[1]);
    if(modfile == NULL) return -2;

    printf("\n%s loaded!\n",argv[1]);
    if(strncmp(modfile->identifier,"M.K.",4) == 0)
    {
        printf("\nValid mod file!\n");
    }
    else
    {
        printf("\nERROR: Not a valid mod file.\nOnly 4 channel mod files with 31 samples allowed.\n\n");
        return -3;
    }

    printf("\nSong name: ");
    for(i = 0; i < 20; i++) if(modfile->name[i]) printf("%c",modfile->name[i]);

    printf("\n\nSample names:\n");

    for(i = 0; i < 31; i++) if(modfile->sample[i].name[0])
        printf("%d: %s\n",i,modfile->sample[i].name);

    printf("\n");

    u8 num_patterns = 0;
    for(i = 0; i < 128; i++) if(modfile->pattern_table[i] > num_patterns)
            num_patterns = modfile->pattern_table[i];
    num_patterns ++;

    printf("Number of patterns: %d\n",num_patterns);

    out_open();

    out_write_str("\n// File created by mod2gbt\n\n","\n; File created by mod2gbt\n\n");

    out_write_str("#pragma bank=","\tSECTION \"");
    out_write_str("",label_name);
    out_write_str("","\", DATA, BANK[");
    out_write_dec(current_output_bank);
    out_write_str("\n\n","]\n\n");

    printf("\nConverting patterns.\n\n");
    for(i = 0; i < num_patterns; i++)
    {
        printf("Pattern %d...\n",i);
        convert_pattern(&(modfile->pattern[i]),i);
    }

    printf("\nPattern order...\n");

    out_write_str("const unsigned char * ","");
    out_write_str(label_name,label_name);
    out_write_str("_Data[] = {\n","_Data::\n");
    for(i = 0; i < modfile->song_lenght; i ++)
    {
        out_write_str("    ","    DW  ");
        out_write_str(label_name,label_name);
        out_write_dec(modfile->pattern_table[i]);
        out_write_str(",\n","\n");
    }
    out_write_str("    0x0000\n","    DW  $0000\n");
    out_write_str("};\n\n","\n\n");

    out_close();

    printf("\nDone!\n\n");

    return 0;
}