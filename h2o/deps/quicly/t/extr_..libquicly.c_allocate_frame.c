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
typedef  int /*<<< orphan*/  quicly_send_context_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */
 int _do_allocate_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allocate_frame(quicly_conn_t *conn, quicly_send_context_t *s, size_t min_space)
{
    return _do_allocate_frame(conn, s, min_space, 0);
}