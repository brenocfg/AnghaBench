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
 char* AGALOC (int /*<<< orphan*/ ,char*) ; 
#define  BEL 135 
#define  BS 134 
#define  CR 133 
#define  FF 132 
#define  HT 131 
#define  LF 130 
 char* MK_STR_OCT_FMT ; 
 char const NL ; 
#define  NUL 129 
#define  VT 128 
 int /*<<< orphan*/  add_esc_ch (char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 
 int /*<<< orphan*/  string_size (char const*,size_t) ; 
 size_t strlen (char const*) ; 

char const *
optionQuoteString(char const * text, char const * nl)
{
    size_t   nl_len = strlen(nl);
    char *   out;
    char *   res = out = AGALOC(string_size(text, nl_len), "quot str");
    *(out++) = '"';

    for (;;) {
        unsigned char ch = (unsigned char)*text;
        if ((ch >= ' ') && (ch <= '~')) {
            if ((ch == '"') || (ch == '\\'))
                /*
                 *  We must escape these characters in the output string
                 */
                *(out++) = '\\';
            *(out++) = (char)ch;

        } else switch (ch) {
#       define   add_esc_ch(_ch)  { *(out++) = '\\'; *(out++) = (_ch); }
        case BEL: add_esc_ch('a'); break;
        case BS:  add_esc_ch('b'); break;
        case HT:  add_esc_ch('t'); break;
        case VT:  add_esc_ch('v'); break;
        case FF:  add_esc_ch('f'); break;
        case CR:  add_esc_ch('r'); break;

        case LF:
            /*
             *  Place contiguous new-lines on a single line.
             *  The current character is a NL, check the next one.
             */
            while (*++text == NL)
                add_esc_ch('n');

            /*
             *  Insert a splice before starting next line
             */
            if (*text != NUL) {
                memcpy(out, nl, nl_len);
                out += nl_len;

                continue; /* text is already at the next character */
            }

            add_esc_ch('n');
            /* FALLTHROUGH */

        case NUL:
            /*
             *  End of string.  Terminate the quoted output.  If necessary,
             *  deallocate the text string.  Return the scan resumption point.
             */
            *(out++) = '"';
            *out = NUL;
            return res;

        default:
            /*
             *  sprintf is safe here, because we already computed
             *  the amount of space we will be using.
             */
            sprintf(out, MK_STR_OCT_FMT, ch);
            out += 4;
        }

        text++;
#       undef add_esc_ch
    }
}