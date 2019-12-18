#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_save_resumption_token_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ptls_iovec_t ;
struct TYPE_7__ {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {TYPE_4__ address_token; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ ptls_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_get_peer_transport_parameters (int /*<<< orphan*/ *) ; 
 int save_session (int /*<<< orphan*/ ) ; 
 TYPE_2__ session_info ; 

__attribute__((used)) static int save_resumption_token_cb(quicly_save_resumption_token_t *_self, quicly_conn_t *conn, ptls_iovec_t token)
{
    free(session_info.address_token.base);
    session_info.address_token = ptls_iovec_init(malloc(token.len), token.len);
    memcpy(session_info.address_token.base, token.base, token.len);

    return save_session(quicly_get_peer_transport_parameters(conn));
}