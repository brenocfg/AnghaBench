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
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_6__ {TYPE_1__ super; } ;
typedef  TYPE_2__ quicly_conn_t ;

/* Variables and functions */
 scalar_t__ QUICLY_ERROR_IS_QUIC_APPLICATION (int) ; 
 int /*<<< orphan*/  QUICLY_FRAME_TYPE_PADDING ; 
 int /*<<< orphan*/  assert (int) ; 
 int initiate_close (TYPE_2__*,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  update_now (int /*<<< orphan*/ ) ; 

int quicly_close(quicly_conn_t *conn, int err, const char *reason_phrase)
{
    assert(err == 0 || QUICLY_ERROR_IS_QUIC_APPLICATION(err));
    update_now(conn->super.ctx);

    return initiate_close(conn, err, QUICLY_FRAME_TYPE_PADDING /* used when err == 0 */, reason_phrase);
}