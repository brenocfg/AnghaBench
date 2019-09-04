#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ ptls_t ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CLIENT_CERTIFICATE_VERIFY_CONTEXT_STRING ; 
 int PTLS_ERROR_IN_PROGRESS ; 
 int /*<<< orphan*/  PTLS_STATE_SERVER_EXPECT_FINISHED ; 
 int handle_certificate_verify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int server_handle_certificate_verify(ptls_t *tls, ptls_iovec_t message)
{
    int ret = handle_certificate_verify(tls, message, PTLS_CLIENT_CERTIFICATE_VERIFY_CONTEXT_STRING);

    if (ret == 0) {
        tls->state = PTLS_STATE_SERVER_EXPECT_FINISHED;
        ret = PTLS_ERROR_IN_PROGRESS;
    }

    return ret;
}