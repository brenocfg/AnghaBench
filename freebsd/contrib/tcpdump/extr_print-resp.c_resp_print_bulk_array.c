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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LENGTH (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  SKIP_OPCODE (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  TEST_RET_LEN_NORETURN (int) ; 
 int resp_parse (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  resp_print_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_print_invalid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_print_length_negative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_print_length_too_large (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resp_print_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
resp_print_bulk_array(netdissect_options *ndo, register const u_char *bp, int length) {
    u_int length_cur = length;
    int array_len, i, ret_len;

    /* bp points to the op; skip it */
    SKIP_OPCODE(bp, length_cur);

    /* <array_length>\r\n */
    GET_LENGTH(ndo, length_cur, bp, array_len);

    if (array_len > 0) {
        /* non empty array */
        for (i = 0; i < array_len; i++) {
            ret_len = resp_parse(ndo, bp, length_cur);

            TEST_RET_LEN_NORETURN(ret_len);

            bp += ret_len;
            length_cur -= ret_len;
        }
    } else {
        /* empty, null, truncated, or invalid */
        switch(array_len) {
            case 0:     resp_print_empty(ndo);            break;
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