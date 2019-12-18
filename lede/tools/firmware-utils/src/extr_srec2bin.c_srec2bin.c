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
typedef  int bit32u ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AddressCurrent ; 
 void* BigEndian ; 
 void* FALSE ; 
 void* RecStart ; 
 void* TRUE ; 
 int /*<<< orphan*/  WaitDisplay () ; 
 int /*<<< orphan*/  binOut32 (int) ; 
 int /*<<< orphan*/  binRecEnd () ; 
 int /*<<< orphan*/  dumpfTell (char*,int) ; 
 int /*<<< orphan*/ * fOut ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ inputline ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int readline (int /*<<< orphan*/ *,char*,int) ; 
 int srecLine (char*) ; 
 scalar_t__ strlen (char*) ; 

int srec2bin(int argc,char *argv[],int verbose)
{
    int i,rlen,sts;
    FILE *fp;
    char ac;
    char buff[256];
    bit32u TAG_BIG     = 0xDEADBE42;
    bit32u TAG_LITTLE  = 0xFEEDFA42;

    bit32u Tag;

  
    if(argc < 3)
    {
      printf("\nError: <srec2bin <srec input file> <bin output file>\n\n");
      return(0);
    }
  
    if (argc > 3) BigEndian=TRUE; else BigEndian=FALSE;

    if (BigEndian)
        Tag = TAG_BIG;
    else
        Tag = TAG_LITTLE;

    if (verbose)
       printf("\nEndian: %s, Tag is 0x%8X\n",(BigEndian)?"BIG":"LITTLE", Tag);

    fp = fopen(argv[1],"rt");

    if (fp==NULL)
    {
      printf("\nError: Opening input file, %s.", argv[1]);
      return(0);
    }
  
    fOut = fopen( argv[2], "wb");
    
    if (fOut==NULL)
    {
      printf("\nError: Opening Output file, %s.", argv[2]);
      if(fp) fclose(fp);
      return(0);
    }
 
    RecStart = FALSE;

    AddressCurrent = 0xFFFFFFFFL;

    // Setup Tag 
  
    dumpfTell("Tag", Tag);

    binOut32(Tag);

  
    inputline=0;
    sts=TRUE;

    rlen = readline(fp,buff,sizeof buff);

    while( (sts) && (rlen != -1))
    {
        if (strlen(buff))
        {
            sts &= srecLine(buff);
            WaitDisplay();
        }
       rlen = readline(fp,buff,sizeof buff);
    }

  
  //  printf("PC: 0x%08X, Length 0x%08X, Tag 0x%08X\n", ProgramStart, RecLength, TAG_LITTLE);
  
    binRecEnd();

    if(fp) fclose(fp);
    if(fOut) fclose(fOut);

    return(1);
}