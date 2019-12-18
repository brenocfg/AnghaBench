#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int state; TYPE_1__* ctx; } ;
typedef  TYPE_2__ ptls_t ;
struct TYPE_4__ {int /*<<< orphan*/  omit_end_of_early_data; } ;

/* Variables and functions */
#define  PTLS_STATE_CLIENT_EXPECT_CERTIFICATE 143 
#define  PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_REQUEST_OR_CERTIFICATE 142 
#define  PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_VERIFY 141 
#define  PTLS_STATE_CLIENT_EXPECT_ENCRYPTED_EXTENSIONS 140 
#define  PTLS_STATE_CLIENT_EXPECT_FINISHED 139 
#define  PTLS_STATE_CLIENT_EXPECT_SECOND_SERVER_HELLO 138 
#define  PTLS_STATE_CLIENT_EXPECT_SERVER_HELLO 137 
#define  PTLS_STATE_CLIENT_HANDSHAKE_START 136 
#define  PTLS_STATE_CLIENT_POST_HANDSHAKE 135 
#define  PTLS_STATE_SERVER_EXPECT_CERTIFICATE 134 
#define  PTLS_STATE_SERVER_EXPECT_CERTIFICATE_VERIFY 133 
#define  PTLS_STATE_SERVER_EXPECT_CLIENT_HELLO 132 
#define  PTLS_STATE_SERVER_EXPECT_END_OF_EARLY_DATA 131 
#define  PTLS_STATE_SERVER_EXPECT_FINISHED 130 
#define  PTLS_STATE_SERVER_EXPECT_SECOND_CLIENT_HELLO 129 
#define  PTLS_STATE_SERVER_POST_HANDSHAKE 128 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

size_t ptls_get_read_epoch(ptls_t *tls)
{
    switch (tls->state) {
    case PTLS_STATE_CLIENT_HANDSHAKE_START:
    case PTLS_STATE_CLIENT_EXPECT_SERVER_HELLO:
    case PTLS_STATE_CLIENT_EXPECT_SECOND_SERVER_HELLO:
    case PTLS_STATE_SERVER_EXPECT_CLIENT_HELLO:
    case PTLS_STATE_SERVER_EXPECT_SECOND_CLIENT_HELLO:
        return 0; /* plaintext */
    case PTLS_STATE_SERVER_EXPECT_END_OF_EARLY_DATA:
        assert(!tls->ctx->omit_end_of_early_data);
        return 1; /* 0-rtt */
    case PTLS_STATE_CLIENT_EXPECT_ENCRYPTED_EXTENSIONS:
    case PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_REQUEST_OR_CERTIFICATE:
    case PTLS_STATE_CLIENT_EXPECT_CERTIFICATE:
    case PTLS_STATE_CLIENT_EXPECT_CERTIFICATE_VERIFY:
    case PTLS_STATE_CLIENT_EXPECT_FINISHED:
    case PTLS_STATE_SERVER_EXPECT_CERTIFICATE:
    case PTLS_STATE_SERVER_EXPECT_CERTIFICATE_VERIFY:
    case PTLS_STATE_SERVER_EXPECT_FINISHED:
        return 2; /* handshake */
    case PTLS_STATE_CLIENT_POST_HANDSHAKE:
    case PTLS_STATE_SERVER_POST_HANDSHAKE:
        return 3; /* 1-rtt */
    default:
        assert(!"invalid state");
        return SIZE_MAX;
    }
}