#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct st_ptls_record_t {size_t member_2; void const* member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct st_ptls_raw_message_emitter_t {size_t* member_2; int /*<<< orphan*/  super; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  enc; } ;
struct TYPE_10__ {TYPE_2__ traffic_protection; } ;
typedef  TYPE_3__ ptls_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;
typedef  int /*<<< orphan*/  ptls_buffer_t ;

/* Variables and functions */
 int PTLS_ALERT_UNEXPECTED_MESSAGE ; 
 int /*<<< orphan*/  PTLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int /*<<< orphan*/  begin_raw_message ; 
 int /*<<< orphan*/  commit_raw_message ; 
 int /*<<< orphan*/  handle_handshake_message ; 
 int handle_handshake_record (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct st_ptls_record_t*,int /*<<< orphan*/ *) ; 
 size_t ptls_get_read_epoch (TYPE_3__*) ; 
 int send_client_hello (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ptls_handle_message(ptls_t *tls, ptls_buffer_t *sendbuf, size_t epoch_offsets[5], size_t in_epoch, const void *input,
                        size_t inlen, ptls_handshake_properties_t *properties)
{
    struct st_ptls_raw_message_emitter_t emitter = {
        {sendbuf, &tls->traffic_protection.enc, 0, begin_raw_message, commit_raw_message}, SIZE_MAX, epoch_offsets};
    struct st_ptls_record_t rec = {PTLS_CONTENT_TYPE_HANDSHAKE, 0, inlen, input};

    if (input == NULL)
        return send_client_hello(tls, &emitter.super, properties, NULL);

    if (ptls_get_read_epoch(tls) != in_epoch)
        return PTLS_ALERT_UNEXPECTED_MESSAGE;

    return handle_handshake_record(tls, handle_handshake_message, &emitter.super, &rec, properties);
}