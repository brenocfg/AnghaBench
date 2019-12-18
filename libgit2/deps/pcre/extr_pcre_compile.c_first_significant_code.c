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
typedef  size_t pcre_uchar ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GET (size_t const*,int) ; 
 size_t const OP_ALT ; 
#define  OP_ASSERTBACK 138 
#define  OP_ASSERTBACK_NOT 137 
#define  OP_ASSERT_NOT 136 
#define  OP_CALLOUT 135 
#define  OP_CREF 134 
#define  OP_DEF 133 
#define  OP_DNCREF 132 
#define  OP_DNRREF 131 
#define  OP_NOT_WORD_BOUNDARY 130 
#define  OP_RREF 129 
#define  OP_WORD_BOUNDARY 128 
 int /*<<< orphan*/  OP_lengths ; 
 int /*<<< orphan*/ * PRIV (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const pcre_uchar*
first_significant_code(const pcre_uchar *code, BOOL skipassert)
{
for (;;)
  {
  switch ((int)*code)
    {
    case OP_ASSERT_NOT:
    case OP_ASSERTBACK:
    case OP_ASSERTBACK_NOT:
    if (!skipassert) return code;
    do code += GET(code, 1); while (*code == OP_ALT);
    code += PRIV(OP_lengths)[*code];
    break;

    case OP_WORD_BOUNDARY:
    case OP_NOT_WORD_BOUNDARY:
    if (!skipassert) return code;
    /* Fall through */

    case OP_CALLOUT:
    case OP_CREF:
    case OP_DNCREF:
    case OP_RREF:
    case OP_DNRREF:
    case OP_DEF:
    code += PRIV(OP_lengths)[*code];
    break;

    default:
    return code;
    }
  }
/* Control never reaches here */
}