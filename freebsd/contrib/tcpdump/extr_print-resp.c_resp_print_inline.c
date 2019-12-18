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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  CONSUME_CR_OR_LF (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  FIND_CR_OR_LF (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  RESP_PRINT_SEGMENT (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
resp_print_inline(netdissect_options *ndo, register const u_char *bp, int length) {
    int length_cur = length;
    int len;
    const u_char *bp_ptr;

    /*
     * Inline commands are simply 'strings' followed by \r or \n or both.
     * Redis will do its best to split/parse these strings.
     * This feature of redis is implemented to support the ability of
     * command parsing from telnet/nc sessions etc.
     *
     * <string><\r||\n||\r\n...>
     */

    /*
     * Skip forward past any leading \r, \n, or \r\n.
     */
    CONSUME_CR_OR_LF(bp, length_cur);
    bp_ptr = bp;

    /*
     * Scan forward looking for \r or \n.
     */
    FIND_CR_OR_LF(bp_ptr, length_cur);

    /*
     * Found it; bp_ptr points to the \r or \n, so bp_ptr - bp is the
     * Length of the line text that preceeds it.  Print it.
     */
    len = (bp_ptr - bp);
    RESP_PRINT_SEGMENT(ndo, bp, len);

    /*
     * Skip forward past the \r, \n, or \r\n.
     */
    CONSUME_CR_OR_LF(bp_ptr, length_cur);

    /*
     * Return the number of bytes we processed.
     */
    return (length - length_cur);

trunc:
    return (-1);
}