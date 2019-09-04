#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  ijkio_manager_ctx; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
#define  FFP_PROP_INT64_IMMEDIATE_RECONNECT 129 
#define  FFP_PROP_INT64_SHARE_CACHE_DATA 128 
 int /*<<< orphan*/  ijkio_manager_did_share_cache_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijkio_manager_immediate_reconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijkio_manager_will_share_cache_map (int /*<<< orphan*/ ) ; 

void ffp_set_property_int64(FFPlayer *ffp, int id, int64_t value)
{
    switch (id) {
        // case FFP_PROP_INT64_SELECTED_VIDEO_STREAM:
        // case FFP_PROP_INT64_SELECTED_AUDIO_STREAM:
        case FFP_PROP_INT64_SHARE_CACHE_DATA:
            if (ffp) {
                if (value) {
                    ijkio_manager_will_share_cache_map(ffp->ijkio_manager_ctx);
                } else {
                    ijkio_manager_did_share_cache_map(ffp->ijkio_manager_ctx);
                }
            }
            break;
        case FFP_PROP_INT64_IMMEDIATE_RECONNECT:
            if (ffp) {
                ijkio_manager_immediate_reconnect(ffp->ijkio_manager_ctx);
            }
        default:
            break;
    }
}