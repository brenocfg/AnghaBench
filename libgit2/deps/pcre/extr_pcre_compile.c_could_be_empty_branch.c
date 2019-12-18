#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t const* group; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ recurse_check ;
typedef  size_t pcre_uchar ;
struct TYPE_6__ {size_t* start_code; size_t* start_workspace; size_t const* hwm; } ;
typedef  TYPE_2__ compile_data ;
typedef  void* BOOL ;

/* Variables and functions */
 void* FALSE ; 
 size_t GET (size_t const*,int) ; 
 int /*<<< orphan*/  GET2 (size_t const*,int) ; 
 int /*<<< orphan*/  GET_EXTRALEN (size_t const) ; 
 int /*<<< orphan*/  HAS_EXTRALEN (size_t const) ; 
 int /*<<< orphan*/  IMM2_SIZE ; 
 int /*<<< orphan*/  LINK_SIZE ; 
#define  OP_ALLANY 237 
#define  OP_ALT 236 
#define  OP_ANY 235 
#define  OP_ANYBYTE 234 
#define  OP_ANYNL 233 
 size_t OP_ASSERT ; 
 size_t OP_BRA ; 
 size_t OP_BRAMINZERO ; 
 size_t OP_BRAPOS ; 
 size_t OP_BRAPOSZERO ; 
 size_t OP_BRAZERO ; 
 size_t OP_CBRA ; 
 size_t OP_CBRAPOS ; 
#define  OP_CHAR 232 
#define  OP_CHARI 231 
#define  OP_CLASS 230 
 size_t OP_COND ; 
#define  OP_CRMINPLUS 229 
#define  OP_CRMINQUERY 228 
#define  OP_CRMINRANGE 227 
#define  OP_CRMINSTAR 226 
#define  OP_CRPLUS 225 
#define  OP_CRPOSPLUS 224 
#define  OP_CRPOSQUERY 223 
#define  OP_CRPOSRANGE 222 
#define  OP_CRPOSSTAR 221 
#define  OP_CRQUERY 220 
#define  OP_CRRANGE 219 
#define  OP_CRSTAR 218 
#define  OP_DIGIT 217 
#define  OP_EXACT 216 
#define  OP_EXACTI 215 
#define  OP_EXTUNI 214 
#define  OP_HSPACE 213 
#define  OP_KET 212 
#define  OP_KETRMAX 211 
#define  OP_KETRMIN 210 
#define  OP_KETRPOS 209 
#define  OP_MARK 208 
#define  OP_MINPLUS 207 
#define  OP_MINPLUSI 206 
#define  OP_MINQUERY 205 
#define  OP_MINQUERYI 204 
#define  OP_MINSTAR 203 
#define  OP_MINSTARI 202 
#define  OP_MINUPTO 201 
#define  OP_MINUPTOI 200 
#define  OP_NCLASS 199 
#define  OP_NOT 198 
#define  OP_NOTEXACT 197 
#define  OP_NOTEXACTI 196 
#define  OP_NOTI 195 
#define  OP_NOTMINPLUS 194 
#define  OP_NOTMINPLUSI 193 
#define  OP_NOTMINQUERY 192 
#define  OP_NOTMINQUERYI 191 
#define  OP_NOTMINSTAR 190 
#define  OP_NOTMINSTARI 189 
#define  OP_NOTMINUPTO 188 
#define  OP_NOTMINUPTOI 187 
#define  OP_NOTPLUS 186 
#define  OP_NOTPLUSI 185 
#define  OP_NOTPOSPLUS 184 
#define  OP_NOTPOSPLUSI 183 
#define  OP_NOTPOSQUERY 182 
#define  OP_NOTPOSQUERYI 181 
#define  OP_NOTPOSSTAR 180 
#define  OP_NOTPOSSTARI 179 
#define  OP_NOTPOSUPTO 178 
#define  OP_NOTPOSUPTOI 177 
#define  OP_NOTPROP 176 
#define  OP_NOTQUERY 175 
#define  OP_NOTQUERYI 174 
#define  OP_NOTSTAR 173 
#define  OP_NOTSTARI 172 
#define  OP_NOTUPTO 171 
#define  OP_NOTUPTOI 170 
#define  OP_NOT_DIGIT 169 
#define  OP_NOT_HSPACE 168 
#define  OP_NOT_VSPACE 167 
#define  OP_NOT_WHITESPACE 166 
#define  OP_NOT_WORDCHAR 165 
 size_t OP_ONCE ; 
 size_t OP_ONCE_NC ; 
#define  OP_PLUS 164 
#define  OP_PLUSI 163 
#define  OP_POSPLUS 162 
#define  OP_POSPLUSI 161 
#define  OP_POSQUERY 160 
#define  OP_POSQUERYI 159 
#define  OP_POSSTAR 158 
#define  OP_POSSTARI 157 
#define  OP_POSUPTO 156 
#define  OP_POSUPTOI 155 
#define  OP_PROP 154 
#define  OP_PRUNE_ARG 153 
#define  OP_QUERY 152 
#define  OP_QUERYI 151 
 size_t OP_RECURSE ; 
 size_t OP_SBRA ; 
 size_t OP_SBRAPOS ; 
 size_t OP_SCBRA ; 
 size_t OP_SCBRAPOS ; 
 size_t OP_SCOND ; 
 size_t OP_SKIPZERO ; 
#define  OP_SKIP_ARG 150 
#define  OP_STAR 149 
#define  OP_STARI 148 
#define  OP_THEN_ARG 147 
#define  OP_TYPEEXACT 146 
#define  OP_TYPEMINPLUS 145 
#define  OP_TYPEMINQUERY 144 
#define  OP_TYPEMINSTAR 143 
#define  OP_TYPEMINUPTO 142 
#define  OP_TYPEPLUS 141 
#define  OP_TYPEPOSPLUS 140 
#define  OP_TYPEPOSQUERY 139 
#define  OP_TYPEPOSSTAR 138 
#define  OP_TYPEPOSUPTO 137 
#define  OP_TYPEQUERY 136 
#define  OP_TYPESTAR 135 
#define  OP_TYPEUPTO 134 
#define  OP_UPTO 133 
#define  OP_UPTOI 132 
#define  OP_VSPACE 131 
#define  OP_WHITESPACE 130 
#define  OP_WORDCHAR 129 
#define  OP_XCLASS 128 
 int /*<<< orphan*/  OP_lengths ; 
 int* PRIV (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 size_t* first_significant_code (size_t const*,void*) ; 

__attribute__((used)) static BOOL
could_be_empty_branch(const pcre_uchar *code, const pcre_uchar *endcode,
  BOOL utf, compile_data *cd, recurse_check *recurses)
{
register pcre_uchar c;
recurse_check this_recurse;

for (code = first_significant_code(code + PRIV(OP_lengths)[*code], TRUE);
     code < endcode;
     code = first_significant_code(code + PRIV(OP_lengths)[c], TRUE))
  {
  const pcre_uchar *ccode;

  c = *code;

  /* Skip over forward assertions; the other assertions are skipped by
  first_significant_code() with a TRUE final argument. */

  if (c == OP_ASSERT)
    {
    do code += GET(code, 1); while (*code == OP_ALT);
    c = *code;
    continue;
    }

  /* For a recursion/subroutine call, if its end has been reached, which
  implies a backward reference subroutine call, we can scan it. If it's a
  forward reference subroutine call, we can't. To detect forward reference
  we have to scan up the list that is kept in the workspace. This function is
  called only when doing the real compile, not during the pre-compile that
  measures the size of the compiled pattern. */

  if (c == OP_RECURSE)
    {
    const pcre_uchar *scode = cd->start_code + GET(code, 1);
    const pcre_uchar *endgroup = scode;
    BOOL empty_branch;

    /* Test for forward reference or uncompleted reference. This is disabled
    when called to scan a completed pattern by setting cd->start_workspace to
    NULL. */

    if (cd->start_workspace != NULL)
      {
      const pcre_uchar *tcode;
      for (tcode = cd->start_workspace; tcode < cd->hwm; tcode += LINK_SIZE)
        if ((int)GET(tcode, 0) == (int)(code + 1 - cd->start_code)) return TRUE;
      if (GET(scode, 1) == 0) return TRUE;    /* Unclosed */
      }

    /* If the reference is to a completed group, we need to detect whether this
    is a recursive call, as otherwise there will be an infinite loop. If it is
    a recursion, just skip over it. Simple recursions are easily detected. For
    mutual recursions we keep a chain on the stack. */

    do endgroup += GET(endgroup, 1); while (*endgroup == OP_ALT);
    if (code >= scode && code <= endgroup) continue;  /* Simple recursion */
    else
      {
      recurse_check *r = recurses;
      for (r = recurses; r != NULL; r = r->prev)
        if (r->group == scode) break;
      if (r != NULL) continue;   /* Mutual recursion */
      }

    /* Completed reference; scan the referenced group, remembering it on the
    stack chain to detect mutual recursions. */

    empty_branch = FALSE;
    this_recurse.prev = recurses;
    this_recurse.group = scode;

    do
      {
      if (could_be_empty_branch(scode, endcode, utf, cd, &this_recurse))
        {
        empty_branch = TRUE;
        break;
        }
      scode += GET(scode, 1);
      }
    while (*scode == OP_ALT);

    if (!empty_branch) return FALSE;  /* All branches are non-empty */
    continue;
    }

  /* Groups with zero repeats can of course be empty; skip them. */

  if (c == OP_BRAZERO || c == OP_BRAMINZERO || c == OP_SKIPZERO ||
      c == OP_BRAPOSZERO)
    {
    code += PRIV(OP_lengths)[c];
    do code += GET(code, 1); while (*code == OP_ALT);
    c = *code;
    continue;
    }

  /* A nested group that is already marked as "could be empty" can just be
  skipped. */

  if (c == OP_SBRA  || c == OP_SBRAPOS ||
      c == OP_SCBRA || c == OP_SCBRAPOS)
    {
    do code += GET(code, 1); while (*code == OP_ALT);
    c = *code;
    continue;
    }

  /* For other groups, scan the branches. */

  if (c == OP_BRA  || c == OP_BRAPOS ||
      c == OP_CBRA || c == OP_CBRAPOS ||
      c == OP_ONCE || c == OP_ONCE_NC ||
      c == OP_COND || c == OP_SCOND)
    {
    BOOL empty_branch;
    if (GET(code, 1) == 0) return TRUE;    /* Hit unclosed bracket */

    /* If a conditional group has only one branch, there is a second, implied,
    empty branch, so just skip over the conditional, because it could be empty.
    Otherwise, scan the individual branches of the group. */

    if (c == OP_COND && code[GET(code, 1)] != OP_ALT)
      code += GET(code, 1);
    else
      {
      empty_branch = FALSE;
      do
        {
        if (!empty_branch && could_be_empty_branch(code, endcode, utf, cd,
          recurses)) empty_branch = TRUE;
        code += GET(code, 1);
        }
      while (*code == OP_ALT);
      if (!empty_branch) return FALSE;   /* All branches are non-empty */
      }

    c = *code;
    continue;
    }

  /* Handle the other opcodes */

  switch (c)
    {
    /* Check for quantifiers after a class. XCLASS is used for classes that
    cannot be represented just by a bit map. This includes negated single
    high-valued characters. The length in PRIV(OP_lengths)[] is zero; the
    actual length is stored in the compiled code, so we must update "code"
    here. */

#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
    case OP_XCLASS:
    ccode = code += GET(code, 1);
    goto CHECK_CLASS_REPEAT;
#endif

    case OP_CLASS:
    case OP_NCLASS:
    ccode = code + PRIV(OP_lengths)[OP_CLASS];

#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
    CHECK_CLASS_REPEAT:
#endif

    switch (*ccode)
      {
      case OP_CRSTAR:            /* These could be empty; continue */
      case OP_CRMINSTAR:
      case OP_CRQUERY:
      case OP_CRMINQUERY:
      case OP_CRPOSSTAR:
      case OP_CRPOSQUERY:
      break;

      default:                   /* Non-repeat => class must match */
      case OP_CRPLUS:            /* These repeats aren't empty */
      case OP_CRMINPLUS:
      case OP_CRPOSPLUS:
      return FALSE;

      case OP_CRRANGE:
      case OP_CRMINRANGE:
      case OP_CRPOSRANGE:
      if (GET2(ccode, 1) > 0) return FALSE;  /* Minimum > 0 */
      break;
      }
    break;

    /* Opcodes that must match a character */

    case OP_ANY:
    case OP_ALLANY:
    case OP_ANYBYTE:

    case OP_PROP:
    case OP_NOTPROP:
    case OP_ANYNL:

    case OP_NOT_HSPACE:
    case OP_HSPACE:
    case OP_NOT_VSPACE:
    case OP_VSPACE:
    case OP_EXTUNI:

    case OP_NOT_DIGIT:
    case OP_DIGIT:
    case OP_NOT_WHITESPACE:
    case OP_WHITESPACE:
    case OP_NOT_WORDCHAR:
    case OP_WORDCHAR:

    case OP_CHAR:
    case OP_CHARI:
    case OP_NOT:
    case OP_NOTI:

    case OP_PLUS:
    case OP_PLUSI:
    case OP_MINPLUS:
    case OP_MINPLUSI:

    case OP_NOTPLUS:
    case OP_NOTPLUSI:
    case OP_NOTMINPLUS:
    case OP_NOTMINPLUSI:

    case OP_POSPLUS:
    case OP_POSPLUSI:
    case OP_NOTPOSPLUS:
    case OP_NOTPOSPLUSI:

    case OP_EXACT:
    case OP_EXACTI:
    case OP_NOTEXACT:
    case OP_NOTEXACTI:

    case OP_TYPEPLUS:
    case OP_TYPEMINPLUS:
    case OP_TYPEPOSPLUS:
    case OP_TYPEEXACT:

    return FALSE;

    /* These are going to continue, as they may be empty, but we have to
    fudge the length for the \p and \P cases. */

    case OP_TYPESTAR:
    case OP_TYPEMINSTAR:
    case OP_TYPEPOSSTAR:
    case OP_TYPEQUERY:
    case OP_TYPEMINQUERY:
    case OP_TYPEPOSQUERY:
    if (code[1] == OP_PROP || code[1] == OP_NOTPROP) code += 2;
    break;

    /* Same for these */

    case OP_TYPEUPTO:
    case OP_TYPEMINUPTO:
    case OP_TYPEPOSUPTO:
    if (code[1 + IMM2_SIZE] == OP_PROP || code[1 + IMM2_SIZE] == OP_NOTPROP)
      code += 2;
    break;

    /* End of branch */

    case OP_KET:
    case OP_KETRMAX:
    case OP_KETRMIN:
    case OP_KETRPOS:
    case OP_ALT:
    return TRUE;

    /* In UTF-8 mode, STAR, MINSTAR, POSSTAR, QUERY, MINQUERY, POSQUERY, UPTO,
    MINUPTO, and POSUPTO and their caseless and negative versions may be
    followed by a multibyte character. */

#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
    case OP_STAR:
    case OP_STARI:
    case OP_NOTSTAR:
    case OP_NOTSTARI:

    case OP_MINSTAR:
    case OP_MINSTARI:
    case OP_NOTMINSTAR:
    case OP_NOTMINSTARI:

    case OP_POSSTAR:
    case OP_POSSTARI:
    case OP_NOTPOSSTAR:
    case OP_NOTPOSSTARI:

    case OP_QUERY:
    case OP_QUERYI:
    case OP_NOTQUERY:
    case OP_NOTQUERYI:

    case OP_MINQUERY:
    case OP_MINQUERYI:
    case OP_NOTMINQUERY:
    case OP_NOTMINQUERYI:

    case OP_POSQUERY:
    case OP_POSQUERYI:
    case OP_NOTPOSQUERY:
    case OP_NOTPOSQUERYI:

    if (utf && HAS_EXTRALEN(code[1])) code += GET_EXTRALEN(code[1]);
    break;

    case OP_UPTO:
    case OP_UPTOI:
    case OP_NOTUPTO:
    case OP_NOTUPTOI:

    case OP_MINUPTO:
    case OP_MINUPTOI:
    case OP_NOTMINUPTO:
    case OP_NOTMINUPTOI:

    case OP_POSUPTO:
    case OP_POSUPTOI:
    case OP_NOTPOSUPTO:
    case OP_NOTPOSUPTOI:

    if (utf && HAS_EXTRALEN(code[1 + IMM2_SIZE])) code += GET_EXTRALEN(code[1 + IMM2_SIZE]);
    break;
#endif

    /* MARK, and PRUNE/SKIP/THEN with an argument must skip over the argument
    string. */

    case OP_MARK:
    case OP_PRUNE_ARG:
    case OP_SKIP_ARG:
    case OP_THEN_ARG:
    code += code[1];
    break;

    /* None of the remaining opcodes are required to match a character. */

    default:
    break;
    }
  }

return TRUE;
}