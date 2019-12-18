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
typedef  int /*<<< orphan*/  quicly_stream_t ;

/* Variables and functions */
 int H2O_HTTP3_ERROR_CLOSED_CRITICAL_STREAM ; 

__attribute__((used)) static int ingress_unistream_on_receive_reset(quicly_stream_t *qs, int err)
{
    return H2O_HTTP3_ERROR_CLOSED_CRITICAL_STREAM;
}