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
struct TYPE_3__ {int /*<<< orphan*/  rlayer; } ;
typedef  int /*<<< orphan*/  SSL3_BUFFER ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/ * RECORD_LAYER_get_rbuf (int /*<<< orphan*/ *) ; 
 unsigned char* SSL3_BUFFER_get_buf (int /*<<< orphan*/ *) ; 
 size_t SSL3_BUFFER_get_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL3_BUFFER_get_offset (int /*<<< orphan*/ *) ; 
 unsigned char SSL3_RT_APPLICATION_DATA ; 
 size_t SSL3_RT_HEADER_LENGTH ; 
 int /*<<< orphan*/  n2s (unsigned char*,size_t) ; 

__attribute__((used)) static int ssl3_record_app_data_waiting(SSL *s)
{
    SSL3_BUFFER *rbuf;
    size_t left, len;
    unsigned char *p;

    rbuf = RECORD_LAYER_get_rbuf(&s->rlayer);

    p = SSL3_BUFFER_get_buf(rbuf);
    if (p == NULL)
        return 0;

    left = SSL3_BUFFER_get_left(rbuf);

    if (left < SSL3_RT_HEADER_LENGTH)
        return 0;

    p += SSL3_BUFFER_get_offset(rbuf);

    /*
     * We only check the type and record length, we will sanity check version
     * etc later
     */
    if (*p != SSL3_RT_APPLICATION_DATA)
        return 0;

    p += 3;
    n2s(p, len);

    if (left < SSL3_RT_HEADER_LENGTH + len)
        return 0;

    return 1;
}