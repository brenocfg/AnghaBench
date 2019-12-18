#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * dp; } ;
typedef  TYPE_1__ FICL_SYSTEM ;
typedef  int /*<<< orphan*/  FICL_DICT ;

/* Variables and functions */
 int /*<<< orphan*/  EDot ; 
 int /*<<< orphan*/  FDot ; 
 int /*<<< orphan*/  FFrom ; 
 int /*<<< orphan*/  FICL_DEFAULT_STACK ; 
 int /*<<< orphan*/  FICL_FALSE ; 
 int /*<<< orphan*/  FW_COMPILE ; 
 int /*<<< orphan*/  FW_DEFAULT ; 
 int /*<<< orphan*/  FW_IMMEDIATE ; 
 int /*<<< orphan*/  Fadd ; 
 int /*<<< orphan*/  Faddi ; 
 int /*<<< orphan*/  Fconstant ; 
 int /*<<< orphan*/  Fdepth ; 
 int /*<<< orphan*/  Fdiv ; 
 int /*<<< orphan*/  Fdivi ; 
 int /*<<< orphan*/  Fdrop ; 
 int /*<<< orphan*/  Fdup ; 
 int /*<<< orphan*/  Ffetch ; 
 int /*<<< orphan*/  FisEqual ; 
 int /*<<< orphan*/  FisGreater ; 
 int /*<<< orphan*/  FisLess ; 
 int /*<<< orphan*/  FminusRoll ; 
 int /*<<< orphan*/  Fminusrot ; 
 int /*<<< orphan*/  Fmul ; 
 int /*<<< orphan*/  Fmuli ; 
 int /*<<< orphan*/  Fnegate ; 
 int /*<<< orphan*/  Fover ; 
 int /*<<< orphan*/  Fpick ; 
 int /*<<< orphan*/  FplusStore ; 
 int /*<<< orphan*/  FquestionDup ; 
 int /*<<< orphan*/  Froll ; 
 int /*<<< orphan*/  Frot ; 
 int /*<<< orphan*/  Fstore ; 
 int /*<<< orphan*/  Fsub ; 
 int /*<<< orphan*/  Fsubi ; 
 int /*<<< orphan*/  Fswap ; 
 int /*<<< orphan*/  Ftoi ; 
 int /*<<< orphan*/  FtwoDrop ; 
 int /*<<< orphan*/  FtwoDup ; 
 int /*<<< orphan*/  FtwoOver ; 
 int /*<<< orphan*/  FtwoSwap ; 
 int /*<<< orphan*/  FzeroEquals ; 
 int /*<<< orphan*/  FzeroGreater ; 
 int /*<<< orphan*/  FzeroLess ; 
 int /*<<< orphan*/  ToF ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictAppendWord (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  displayFStack ; 
 int /*<<< orphan*/  ficlSetEnv (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fliteralIm ; 
 int /*<<< orphan*/  fliteralParen ; 
 int /*<<< orphan*/  idivf ; 
 int /*<<< orphan*/  isubf ; 
 int /*<<< orphan*/  itof ; 

void ficlCompileFloat(FICL_SYSTEM *pSys)
{
    FICL_DICT *dp = pSys->dp;
    assert(dp);

#if FICL_WANT_FLOAT
    dictAppendWord(dp, ">float",    ToF,            FW_DEFAULT);
    /* d>f */
    dictAppendWord(dp, "f!",        Fstore,         FW_DEFAULT);
    dictAppendWord(dp, "f*",        Fmul,           FW_DEFAULT);
    dictAppendWord(dp, "f+",        Fadd,           FW_DEFAULT);
    dictAppendWord(dp, "f-",        Fsub,           FW_DEFAULT);
    dictAppendWord(dp, "f/",        Fdiv,           FW_DEFAULT);
    dictAppendWord(dp, "f0<",       FzeroLess,      FW_DEFAULT);
    dictAppendWord(dp, "f0=",       FzeroEquals,    FW_DEFAULT);
    dictAppendWord(dp, "f<",        FisLess,        FW_DEFAULT);
 /* 
    f>d 
 */
    dictAppendWord(dp, "f@",        Ffetch,         FW_DEFAULT);
 /* 
    falign 
    faligned 
 */
    dictAppendWord(dp, "fconstant", Fconstant,      FW_DEFAULT);
    dictAppendWord(dp, "fdepth",    Fdepth,         FW_DEFAULT);
    dictAppendWord(dp, "fdrop",     Fdrop,          FW_DEFAULT);
    dictAppendWord(dp, "fdup",      Fdup,           FW_DEFAULT);
    dictAppendWord(dp, "fliteral",  fliteralIm,     FW_IMMEDIATE);
/*
    float+
    floats
    floor
    fmax
    fmin
*/
    dictAppendWord(dp, "f?dup",     FquestionDup,   FW_DEFAULT);
    dictAppendWord(dp, "f=",        FisEqual,       FW_DEFAULT);
    dictAppendWord(dp, "f>",        FisGreater,     FW_DEFAULT);
    dictAppendWord(dp, "f0>",       FzeroGreater,   FW_DEFAULT);
    dictAppendWord(dp, "f2drop",    FtwoDrop,       FW_DEFAULT);
    dictAppendWord(dp, "f2dup",     FtwoDup,        FW_DEFAULT);
    dictAppendWord(dp, "f2over",    FtwoOver,       FW_DEFAULT);
    dictAppendWord(dp, "f2swap",    FtwoSwap,       FW_DEFAULT);
    dictAppendWord(dp, "f+!",       FplusStore,     FW_DEFAULT);
    dictAppendWord(dp, "f+i",       Faddi,          FW_DEFAULT);
    dictAppendWord(dp, "f-i",       Fsubi,          FW_DEFAULT);
    dictAppendWord(dp, "f*i",       Fmuli,          FW_DEFAULT);
    dictAppendWord(dp, "f/i",       Fdivi,          FW_DEFAULT);
    dictAppendWord(dp, "int>float", itof,           FW_DEFAULT);
    dictAppendWord(dp, "float>int", Ftoi,           FW_DEFAULT);
    dictAppendWord(dp, "f.",        FDot,           FW_DEFAULT);
    dictAppendWord(dp, "f.s",       displayFStack,  FW_DEFAULT);
    dictAppendWord(dp, "fe.",       EDot,           FW_DEFAULT);
    dictAppendWord(dp, "fover",     Fover,          FW_DEFAULT);
    dictAppendWord(dp, "fnegate",   Fnegate,        FW_DEFAULT);
    dictAppendWord(dp, "fpick",     Fpick,          FW_DEFAULT);
    dictAppendWord(dp, "froll",     Froll,          FW_DEFAULT);
    dictAppendWord(dp, "frot",      Frot,           FW_DEFAULT);
    dictAppendWord(dp, "fswap",     Fswap,          FW_DEFAULT);
    dictAppendWord(dp, "i-f",       isubf,          FW_DEFAULT);
    dictAppendWord(dp, "i/f",       idivf,          FW_DEFAULT);

    dictAppendWord(dp, "float>",    FFrom,          FW_DEFAULT);

    dictAppendWord(dp, "f-roll",    FminusRoll,     FW_DEFAULT);
    dictAppendWord(dp, "f-rot",     Fminusrot,      FW_DEFAULT);
    dictAppendWord(dp, "(fliteral)", fliteralParen, FW_COMPILE);

    ficlSetEnv(pSys, "floating",       FICL_FALSE);  /* not all required words are present */
    ficlSetEnv(pSys, "floating-ext",   FICL_FALSE);
    ficlSetEnv(pSys, "floating-stack", FICL_DEFAULT_STACK);
#endif
    return;
}