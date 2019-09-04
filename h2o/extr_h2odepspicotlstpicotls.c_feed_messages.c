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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptls_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;
struct TYPE_4__ {scalar_t__ off; } ;
typedef  TYPE_1__ ptls_buffer_t ;

/* Variables and functions */
 int PTLS_ERROR_IN_PROGRESS ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int ptls_handle_message (int /*<<< orphan*/ *,TYPE_1__*,size_t*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int feed_messages(ptls_t *tls, ptls_buffer_t *outbuf, size_t *out_epoch_offsets, const uint8_t *input,
                         const size_t *in_epoch_offsets, ptls_handshake_properties_t *props)
{
    size_t i;
    int ret = PTLS_ERROR_IN_PROGRESS;

    outbuf->off = 0;
    memset(out_epoch_offsets, 0, sizeof(*out_epoch_offsets) * 5);

    for (i = 0; i != 4; ++i) {
        size_t len = in_epoch_offsets[i + 1] - in_epoch_offsets[i];
        if (len != 0) {
            ret = ptls_handle_message(tls, outbuf, out_epoch_offsets, i, input + in_epoch_offsets[i], len, props);
            if (!(ret == 0 || ret == PTLS_ERROR_IN_PROGRESS))
                break;
        }
    }

    return ret;
}