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
typedef  scalar_t__ uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  IS_HEX_DIGIT_CHAR (char const) ; 
 int /*<<< orphan*/  IS_OCT_DIGIT_CHAR (char const) ; 
#define  NL 129 
#define  NUL 128 
 unsigned long strtoul (char*,int /*<<< orphan*/ *,int) ; 

unsigned int
ao_string_cook_escape_char(char const * pzIn, char * pRes, uint_t nl)
{
    unsigned int res = 1;

    switch (*pRes = *pzIn++) {
    case NUL:         /* NUL - end of input string */
        return 0;
    case '\r':
        if (*pzIn != NL)
            return 1;
        res++;
        /* FALLTHROUGH */
    case NL:        /* NL  - emit newline        */
        *pRes = (char)nl;
        return res;

    case 'a': *pRes = '\a'; break;
    case 'b': *pRes = '\b'; break;
    case 'f': *pRes = '\f'; break;
    case 'n': *pRes = NL;   break;
    case 'r': *pRes = '\r'; break;
    case 't': *pRes = '\t'; break;
    case 'v': *pRes = '\v'; break;

    case 'x':
    case 'X':         /* HEX Escape       */
        if (IS_HEX_DIGIT_CHAR(*pzIn))  {
            char z[4];
            unsigned int ct = 0;

            do  {
                z[ct] = pzIn[ct];
                if (++ct >= 2)
                    break;
            } while (IS_HEX_DIGIT_CHAR(pzIn[ct]));
            z[ct] = NUL;
            *pRes = (char)strtoul(z, NULL, 16);
            return ct + 1;
        }
        break;

    case '0': case '1': case '2': case '3':
    case '4': case '5': case '6': case '7':
    {
        /*
         *  IF the character copied was an octal digit,
         *  THEN set the output character to an octal value.
         *  The 3 octal digit result might exceed 0xFF, so check it.
         */
        char z[4];
        unsigned long val;
        unsigned int  ct = 0;

        z[ct++] = *--pzIn;
        while (IS_OCT_DIGIT_CHAR(pzIn[ct])) {
            z[ct] = pzIn[ct];
            if (++ct >= 3)
                break;
        }

        z[ct] = NUL;
        val = strtoul(z, NULL, 8);
        if (val > 0xFF)
            val = 0xFF;
        *pRes = (char)val;
        return ct;
    }

    default: /* quoted character is result character */;
    }

    return res;
}