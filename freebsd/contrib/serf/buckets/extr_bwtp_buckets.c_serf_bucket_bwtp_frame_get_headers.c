#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_9__ {TYPE_1__* headers; } ;
typedef  TYPE_2__ incoming_context_t ;
typedef  TYPE_2__ frame_context_t ;

/* Variables and functions */
 scalar_t__ SERF_BUCKET_IS_BWTP_FRAME (TYPE_1__*) ; 
 scalar_t__ SERF_BUCKET_IS_BWTP_INCOMING_FRAME (TYPE_1__*) ; 

serf_bucket_t *serf_bucket_bwtp_frame_get_headers(
    serf_bucket_t *bucket)
{
    if (SERF_BUCKET_IS_BWTP_FRAME(bucket)) {
        frame_context_t *ctx = bucket->data;

        return ctx->headers;
    }
    else if (SERF_BUCKET_IS_BWTP_INCOMING_FRAME(bucket)) {
        incoming_context_t *ctx = bucket->data;

        return ctx->headers;
    }

    return NULL;
}