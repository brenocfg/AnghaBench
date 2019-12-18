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
 size_t const OP_ALLANY ; 
 size_t const OP_ALT ; 
 int OP_ASSERT ; 
 int OP_BRA ; 
 int OP_BRAPOS ; 
 int OP_CBRA ; 
 int OP_CBRAPOS ; 
 int OP_CIRC ; 
 int OP_COND ; 
 int OP_ONCE ; 
 int OP_ONCE_NC ; 
 int OP_SBRA ; 
 int OP_SBRAPOS ; 
 int OP_SCBRA ; 
 int OP_SCBRAPOS ; 
 int OP_SOD ; 
 int OP_SOM ; 
 int OP_TYPEMINSTAR ; 
 int OP_TYPEPOSSTAR ; 
 int OP_TYPESTAR ; 
 int /*<<< orphan*/  OP_lengths ; 
 int* PRIV (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 size_t* first_significant_code (size_t const*,void*) ; 

__attribute__((used)) static BOOL
is_anchored(register const pcre_uchar *code, unsigned int bracket_map,
  compile_data *cd, int atomcount)
{
do {
   const pcre_uchar *scode = first_significant_code(
     code + PRIV(OP_lengths)[*code], FALSE);
   register int op = *scode;

   /* Non-capturing brackets */

   if (op == OP_BRA  || op == OP_BRAPOS ||
       op == OP_SBRA || op == OP_SBRAPOS)
     {
     if (!is_anchored(scode, bracket_map, cd, atomcount)) return FALSE;
     }

   /* Capturing brackets */

   else if (op == OP_CBRA  || op == OP_CBRAPOS ||
            op == OP_SCBRA || op == OP_SCBRAPOS)
     {
     int n = GET2(scode, 1+LINK_SIZE);
     int new_map = bracket_map | ((n < 32)? (1 << n) : 1);
     if (!is_anchored(scode, new_map, cd, atomcount)) return FALSE;
     }

   /* Positive forward assertions and conditions */

   else if (op == OP_ASSERT || op == OP_COND)
     {
     if (!is_anchored(scode, bracket_map, cd, atomcount)) return FALSE;
     }

   /* Atomic groups */

   else if (op == OP_ONCE || op == OP_ONCE_NC)
     {
     if (!is_anchored(scode, bracket_map, cd, atomcount + 1))
       return FALSE;
     }

   /* .* is not anchored unless DOTALL is set (which generates OP_ALLANY) and
   it isn't in brackets that are or may be referenced or inside an atomic
   group. */

   else if ((op == OP_TYPESTAR || op == OP_TYPEMINSTAR ||
             op == OP_TYPEPOSSTAR))
     {
     if (scode[1] != OP_ALLANY || (bracket_map & cd->backref_map) != 0 ||
         atomcount > 0 || cd->had_pruneorskip)
       return FALSE;
     }

   /* Check for explicit anchoring */

   else if (op != OP_SOD && op != OP_SOM && op != OP_CIRC) return FALSE;

   code += GET(code, 1);
   }
while (*code == OP_ALT);   /* Loop for each alternative */
return TRUE;
}