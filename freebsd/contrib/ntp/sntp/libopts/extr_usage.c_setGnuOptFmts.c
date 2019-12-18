#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fOptSet; } ;
typedef  TYPE_1__ tOptions ;
struct TYPE_5__ {char* pzStr; char const* pzReq; char* pzNum; char* pzKey; char* pzBool; char* pzOpt; char const* pzNo; void* pzOptFmt; int /*<<< orphan*/  pzSpc; int /*<<< orphan*/  pzNoF; int /*<<< orphan*/  pzBrk; int /*<<< orphan*/  pzNest; int /*<<< orphan*/  pzFile; int /*<<< orphan*/  pzTime; int /*<<< orphan*/  pzKeyL; } ;

/* Variables and functions */
#define  OPTPROC_LONGOPT 130 
#define  OPTPROC_L_N_S 129 
#define  OPTPROC_SHORTOPT 128 
 TYPE_3__ argTypes ; 
 char* zGnuBoolArg ; 
 int /*<<< orphan*/  zGnuBreak ; 
 int /*<<< orphan*/  zGnuFileArg ; 
 char* zGnuKeyArg ; 
 int /*<<< orphan*/  zGnuKeyLArg ; 
 int /*<<< orphan*/  zGnuNestArg ; 
 char* zGnuNumArg ; 
 char* zGnuOptArg ; 
 void* zGnuOptFmt ; 
 char* zGnuStrArg ; 
 int /*<<< orphan*/  zGnuTimeArg ; 
 char* zNoRq_ShrtTtl ; 
 void* zShrtGnuOptFmt ; 
 int /*<<< orphan*/  zSixSpaces ; 
 int /*<<< orphan*/  zThreeSpaces ; 

__attribute__((used)) static int
setGnuOptFmts(tOptions * opts, char const ** ptxt)
{
    static char const zOneSpace[] = " ";
    int  flen = 22;
    *ptxt = zNoRq_ShrtTtl;

    argTypes.pzStr  = zGnuStrArg;
    argTypes.pzReq  = zOneSpace;
    argTypes.pzNum  = zGnuNumArg;
    argTypes.pzKey  = zGnuKeyArg;
    argTypes.pzKeyL = zGnuKeyLArg;
    argTypes.pzTime = zGnuTimeArg;
    argTypes.pzFile = zGnuFileArg;
    argTypes.pzBool = zGnuBoolArg;
    argTypes.pzNest = zGnuNestArg;
    argTypes.pzOpt  = zGnuOptArg;
    argTypes.pzNo   = zOneSpace;
    argTypes.pzBrk  = zGnuBreak;
    argTypes.pzNoF  = zSixSpaces;
    argTypes.pzSpc  = zThreeSpaces;

    switch (opts->fOptSet & OPTPROC_L_N_S) {
    case OPTPROC_L_N_S:    argTypes.pzOptFmt = zGnuOptFmt;     break;
    case OPTPROC_LONGOPT:  argTypes.pzOptFmt = zGnuOptFmt;     break;
    case 0:                argTypes.pzOptFmt = zGnuOptFmt + 2; break;
    case OPTPROC_SHORTOPT:
        argTypes.pzOptFmt = zShrtGnuOptFmt;
        zGnuStrArg[0] = zGnuNumArg[0] = zGnuKeyArg[0] = zGnuBoolArg[0] = ' ';
        argTypes.pzOpt = " [arg]";
        flen = 8;
        break;
    }

    return flen;
}