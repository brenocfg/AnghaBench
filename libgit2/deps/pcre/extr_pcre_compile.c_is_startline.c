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
typedef  size_t pcre_uchar ;
struct TYPE_3__ {unsigned int backref_map; scalar_t__ had_pruneorskip; } ;
typedef  TYPE_1__ compile_data ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  GET (size_t const*,int) ; 
 int GET2 (size_t const*,scalar_t__) ; 
 scalar_t__ LINK_SIZE ; 
 size_t const OP_ALT ; 
 size_t const OP_ANY ; 
 int OP_ASSERT ; 
 int OP_BRA ; 
 int OP_BRAPOS ; 
 size_t const OP_CALLOUT ; 
 int OP_CBRA ; 
 int OP_CBRAPOS ; 
 int OP_CIRC ; 
 int OP_CIRCM ; 
 int OP_COND ; 
#define  OP_CREF 133 
#define  OP_DEF 132 
#define  OP_DNCREF 131 
#define  OP_DNRREF 130 
#define  OP_FAIL 129 
 int OP_ONCE ; 
 int OP_ONCE_NC ; 
#define  OP_RREF 128 
 int OP_SBRA ; 
 int OP_SBRAPOS ; 
 int OP_SCBRA ; 
 int OP_SCBRAPOS ; 
 int OP_TYPEMINSTAR ; 
 int OP_TYPEPOSSTAR ; 
 int OP_TYPESTAR ; 
 int /*<<< orphan*/  OP_lengths ; 
 int* PRIV (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 size_t* first_significant_code (size_t const*,void*) ; 

__attribute__((used)) static BOOL
is_startline(const pcre_uchar *code, unsigned int bracket_map,
  compile_data *cd, int atomcount, BOOL inassert)
{
do {
   const pcre_uchar *scode = first_significant_code(
     code + PRIV(OP_lengths)[*code], FALSE);
   register int op = *scode;

   /* If we are at the start of a conditional assertion group, *both* the
   conditional assertion *and* what follows the condition must satisfy the test
   for start of line. Other kinds of condition fail. Note that there may be an
   auto-callout at the start of a condition. */

   if (op == OP_COND)
     {
     scode += 1 + LINK_SIZE;
     if (*scode == OP_CALLOUT) scode += PRIV(OP_lengths)[OP_CALLOUT];
     switch (*scode)
       {
       case OP_CREF:
       case OP_DNCREF:
       case OP_RREF:
       case OP_DNRREF:
       case OP_DEF:
       case OP_FAIL:
       return FALSE;

       default:     /* Assertion */
       if (!is_startline(scode, bracket_map, cd, atomcount, TRUE)) return FALSE;
       do scode += GET(scode, 1); while (*scode == OP_ALT);
       scode += 1 + LINK_SIZE;
       break;
       }
     scode = first_significant_code(scode, FALSE);
     op = *scode;
     }

   /* Non-capturing brackets */

   if (op == OP_BRA  || op == OP_BRAPOS ||
       op == OP_SBRA || op == OP_SBRAPOS)
     {
     if (!is_startline(scode, bracket_map, cd, atomcount, inassert)) return FALSE;
     }

   /* Capturing brackets */

   else if (op == OP_CBRA  || op == OP_CBRAPOS ||
            op == OP_SCBRA || op == OP_SCBRAPOS)
     {
     int n = GET2(scode, 1+LINK_SIZE);
     int new_map = bracket_map | ((n < 32)? (1 << n) : 1);
     if (!is_startline(scode, new_map, cd, atomcount, inassert)) return FALSE;
     }

   /* Positive forward assertions */

   else if (op == OP_ASSERT)
     {
     if (!is_startline(scode, bracket_map, cd, atomcount, TRUE)) return FALSE;
     }

   /* Atomic brackets */

   else if (op == OP_ONCE || op == OP_ONCE_NC)
     {
     if (!is_startline(scode, bracket_map, cd, atomcount + 1, inassert)) return FALSE;
     }

   /* .* means "start at start or after \n" if it isn't in atomic brackets or
   brackets that may be referenced or an assertion, as long as the pattern does
   not contain *PRUNE or *SKIP, because these break the feature. Consider, for
   example, /.*?a(*PRUNE)b/ with the subject "aab", which matches "ab", i.e.
   not at the start of a line. */

   else if (op == OP_TYPESTAR || op == OP_TYPEMINSTAR || op == OP_TYPEPOSSTAR)
     {
     if (scode[1] != OP_ANY || (bracket_map & cd->backref_map) != 0 ||
         atomcount > 0 || cd->had_pruneorskip || inassert)
       return FALSE;
     }

   /* Check for explicit circumflex; anything else gives a FALSE result. Note
   in particular that this includes atomic brackets OP_ONCE and OP_ONCE_NC
   because the number of characters matched by .* cannot be adjusted inside
   them. */

   else if (op != OP_CIRC && op != OP_CIRCM) return FALSE;

   /* Move on to the next alternative */

   code += GET(code, 1);
   }
while (*code == OP_ALT);  /* Loop for each alternative */
return TRUE;
}