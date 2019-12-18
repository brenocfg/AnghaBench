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
 int CheckSum ; 
 scalar_t__ FALSE ; 
 int RecLength ; 
 scalar_t__ RecStart ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  binOut32 (int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  dumpfTell (char*,int) ; 
 int /*<<< orphan*/  fOut ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,...) ; 
 scalar_t__ verbose ; 

void binRecEnd(void)
{
    long RecEnd;

    if (!RecStart)   //  if no record started, do not end it
    {
        return;
    }

    RecStart = FALSE;


    RecEnd = ftell(fOut);         // Save Current position

    if (debug)
          printf("[RecEnd  ] CheckSum[0x%08X] Length[%4d] Length[0x%X] RecEnd[0x%08lX]\n",
                CheckSum, RecLength, RecLength, RecEnd);

    fseek( fOut, -((long) RecLength), SEEK_CUR);  // move back Start Of Data

    dumpfTell("Data   ", -1);

    fseek( fOut, -4, SEEK_CUR);  // move back Start Of Address

    dumpfTell("Address   ", -1);

    fseek( fOut, -4, SEEK_CUR);  // move back Start Of Length

    dumpfTell("Length   ", -1);

    binOut32( RecLength );

    fseek( fOut, RecEnd, SEEK_SET);  // move to end of Record

    CheckSum += RecLength;

    CheckSum =  ~CheckSum + 1;  // Two's complement

    binOut32( CheckSum );

    if (verbose)
        printf("[Created Record of %d Bytes with CheckSum [0x%8X]\n", RecLength, CheckSum);
}