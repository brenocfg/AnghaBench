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
typedef  int /*<<< orphan*/  WORDKIND ;
struct TYPE_3__ {scalar_t__ code; } ;
typedef  TYPE_1__ FICL_WORD ;
typedef  scalar_t__ FICL_CODE ;

/* Variables and functions */
#define  BRANCH 159 
#define  COLON 158 
#define  CONSTANT 157 
#define  CREATE 156 
#define  CSTRINGLIT 155 
#define  DO 154 
#define  DOES 153 
#define  IF 152 
#define  LITERAL 151 
#define  LOOP 150 
#define  OF 149 
#define  PLOOP 148 
 int /*<<< orphan*/  PRIMITIVE ; 
#define  QDO 147 
#define  STRINGLIT 146 
#define  USER 145 
#define  VARIABLE 144 
#define  branch0 143 
#define  branchParen 142 
#define  colonParen 141 
#define  constantParen 140 
#define  createParen 139 
#define  cstringLit 138 
#define  doDoes 137 
#define  doParen 136 
#define  literalParen 135 
#define  loopParen 134 
 int nMAP ; 
#define  ofParen 133 
#define  plusLoopParen 132 
#define  qDoParen 131 
#define  stringLit 130 
#define  userParen 129 
#define  variableParen 128 

WORDKIND ficlWordClassify(FICL_WORD *pFW)
{
    typedef struct 
    {
        WORDKIND kind;
        FICL_CODE code;
    } CODEtoKIND;

    static CODEtoKIND codeMap[] =
    {
        {BRANCH,     branchParen},
        {COLON,       colonParen},
        {CONSTANT, constantParen},
        {CREATE,     createParen},
        {DO,             doParen},
        {DOES,            doDoes},
        {IF,             branch0},
        {LITERAL,   literalParen},
        {LOOP,         loopParen},
        {OF,             ofParen},
        {PLOOP,    plusLoopParen},
        {QDO,           qDoParen},
        {CSTRINGLIT,  cstringLit},
        {STRINGLIT,    stringLit},
#if FICL_WANT_USER
        {USER,         userParen},
#endif
        {VARIABLE, variableParen},
    };

#define nMAP (sizeof(codeMap) / sizeof(CODEtoKIND))

    FICL_CODE code = pFW->code;
    int i;

    for (i=0; i < nMAP; i++)
    {
        if (codeMap[i].code == code)
            return codeMap[i].kind;
    }

    return PRIMITIVE;
}