#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct st_quicly_pending_path_challenge_t {int is_response; struct st_quicly_pending_path_challenge_t* next; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {struct st_quicly_pending_path_challenge_t** tail_ref; } ;
struct TYPE_5__ {TYPE_2__ path_challenge; } ;
struct TYPE_7__ {TYPE_1__ egress; } ;
typedef  TYPE_3__ quicly_conn_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  QUICLY_PATH_CHALLENGE_DATA_LEN ; 
 struct st_quicly_pending_path_challenge_t* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int schedule_path_challenge(quicly_conn_t *conn, int is_response, const uint8_t *data)
{
    struct st_quicly_pending_path_challenge_t *pending;

    if ((pending = malloc(sizeof(struct st_quicly_pending_path_challenge_t))) == NULL)
        return PTLS_ERROR_NO_MEMORY;

    pending->next = NULL;
    pending->is_response = is_response;
    memcpy(pending->data, data, QUICLY_PATH_CHALLENGE_DATA_LEN);

    *conn->egress.path_challenge.tail_ref = pending;
    conn->egress.path_challenge.tail_ref = &pending->next;
    return 0;
}