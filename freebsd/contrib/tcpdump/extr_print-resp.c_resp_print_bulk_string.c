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
 int /*<<< orphan*/  CONSUME_CRLF (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  FIND_CRLF (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  GET_LENGTH (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  LCHECK2 (int,int) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  RESP_PRINT_SEGMENT (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SKIP_OPCODE (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  resp_print_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_print_invalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_print_length_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_print_length_too_large (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_print_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
resp_print_bulk_string(netdissect_options *ndo, register const u_char *bp, int length) {
    int length_cur = length, string_len;

    /* bp points to the op; skip it */
    SKIP_OPCODE(bp, length_cur);

    /* <length>\r\n */
    GET_LENGTH(ndo, length_cur, bp, string_len);

    if (string_len >= 0) {
        /* Byte string of length string_len, starting at bp */
        if (string_len == 0)
            resp_print_empty(ndo);
        else {
            LCHECK2(length_cur, string_len);
            ND_TCHECK2(*bp, string_len);
            RESP_PRINT_SEGMENT(ndo, bp, string_len);
            bp += string_len;
            length_cur -= string_len;
        }

        /*
         * Find the \r\n at the end of the string and skip past it.
         * XXX - report an error if the \r\n isn't immediately after
         * the item?
         */
        FIND_CRLF(bp, length_cur);
        CONSUME_CRLF(bp, length_cur);
    } else {
        /* null, truncated, or invalid for some reason */
        switch(string_len) {
            case (-1):  resp_print_null(ndo);             break;
            case (-2):  goto trunc;
            case (-3):  resp_print_length_too_large(ndo); break;
            case (-4):  resp_print_length_negative(ndo);  break;
            default:    resp_print_invalid(ndo);          break;
        }
    }

    return (length - length_cur);

trunc:
    return (-1);
}