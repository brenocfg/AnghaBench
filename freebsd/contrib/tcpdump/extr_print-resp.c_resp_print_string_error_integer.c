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
 int /*<<< orphan*/  FIND_CRLF (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  RESP_PRINT_SEGMENT (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SKIP_OPCODE (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  TEST_RET_LEN (int) ; 

__attribute__((used)) static int
resp_print_string_error_integer(netdissect_options *ndo, register const u_char *bp, int length) {
    int length_cur = length, len, ret_len;
    const u_char *bp_ptr;

    /* bp points to the op; skip it */
    SKIP_OPCODE(bp, length_cur);
    bp_ptr = bp;

    /*
     * bp now prints past the (+-;) opcode, so it's pointing to the first
     * character of the string (which could be numeric).
     * +OK\r\n
     * -ERR ...\r\n
     * :02912309\r\n
     *
     * Find the \r\n with FIND_CRLF().
     */
    FIND_CRLF(bp_ptr, length_cur);

    /*
     * bp_ptr points to the \r\n, so bp_ptr - bp is the length of text
     * preceding the \r\n.  That includes the opcode, so don't print
     * that.
     */
    len = (bp_ptr - bp);
    RESP_PRINT_SEGMENT(ndo, bp, len);
    ret_len = 1 /*<opcode>*/ + len /*<string>*/ + 2 /*<CRLF>*/;

    TEST_RET_LEN(ret_len);

trunc:
    return (-1);
}