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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  LCHECK2 (int,int) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
#define  RESP_ARRAY 132 
#define  RESP_BULK_STRING 131 
#define  RESP_ERROR 130 
#define  RESP_INTEGER 129 
#define  RESP_SIMPLE_STRING 128 
 int /*<<< orphan*/  TEST_RET_LEN (int) ; 
 int resp_print_bulk_array (int /*<<< orphan*/ *,int const*,int) ; 
 int resp_print_bulk_string (int /*<<< orphan*/ *,int const*,int) ; 
 int resp_print_error (int /*<<< orphan*/ *,int const*,int) ; 
 int resp_print_inline (int /*<<< orphan*/ *,int const*,int) ; 
 int resp_print_integer (int /*<<< orphan*/ *,int const*,int) ; 
 int resp_print_simple_string (int /*<<< orphan*/ *,int const*,int) ; 

__attribute__((used)) static int
resp_parse(netdissect_options *ndo, register const u_char *bp, int length)
{
    u_char op;
    int ret_len;

    LCHECK2(length, 1);
    ND_TCHECK(*bp);
    op = *bp;

    /* bp now points to the op, so these routines must skip it */
    switch(op) {
        case RESP_SIMPLE_STRING:  ret_len = resp_print_simple_string(ndo, bp, length);   break;
        case RESP_INTEGER:        ret_len = resp_print_integer(ndo, bp, length);         break;
        case RESP_ERROR:          ret_len = resp_print_error(ndo, bp, length);           break;
        case RESP_BULK_STRING:    ret_len = resp_print_bulk_string(ndo, bp, length);     break;
        case RESP_ARRAY:          ret_len = resp_print_bulk_array(ndo, bp, length);      break;
        default:                  ret_len = resp_print_inline(ndo, bp, length);          break;
    }

    /*
     * This gives up with a "truncated" indicator for all errors,
     * including invalid packet errors; that's what we want, as
     * we have to give up on further parsing in that case.
     */
    TEST_RET_LEN(ret_len);

trunc:
    return (-1);
}