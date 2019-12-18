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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_CODE (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static uint8_t *encode_status(uint8_t *dst, int status)
{
    /* see also: STATUS_HEADER_MAX_SIZE */

    assert(100 <= status && status <= 999);

    switch (status) {
#define COMMON_CODE(code, st)                                                                                                      \
    case st:                                                                                                                       \
        *dst++ = 0x80 | code;                                                                                                      \
        break
        COMMON_CODE(8, 200);
        COMMON_CODE(9, 204);
        COMMON_CODE(10, 206);
        COMMON_CODE(11, 304);
        COMMON_CODE(12, 400);
        COMMON_CODE(13, 404);
        COMMON_CODE(14, 500);
#undef COMMON_CODE
    default:
        /* use literal header field without indexing - indexed name */
        *dst++ = 8;
        *dst++ = 3;
        sprintf((char *)dst, "%d", status);
        dst += 3;
        break;
    }

    return dst;
}