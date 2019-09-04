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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int header_table_size; int enable_push; int max_concurrent_streams; int initial_window_size; int max_frame_size; } ;
typedef  TYPE_1__ h2o_http2_settings_t ;

/* Variables and functions */
 int H2O_HTTP2_ERROR_FLOW_CONTROL ; 
 int H2O_HTTP2_ERROR_FRAME_SIZE ; 
 int H2O_HTTP2_ERROR_PROTOCOL ; 
#define  H2O_HTTP2_SETTINGS_ENABLE_PUSH 132 
#define  H2O_HTTP2_SETTINGS_HEADER_TABLE_SIZE 131 
#define  H2O_HTTP2_SETTINGS_INITIAL_WINDOW_SIZE 130 
#define  H2O_HTTP2_SETTINGS_MAX_CONCURRENT_STREAMS 129 
#define  H2O_HTTP2_SETTINGS_MAX_FRAME_SIZE 128 
 int UINT32_MAX ; 
 int h2o_http2_decode16u (int /*<<< orphan*/  const*) ; 
 int h2o_http2_decode32u (int /*<<< orphan*/  const*) ; 

int h2o_http2_update_peer_settings(h2o_http2_settings_t *settings, const uint8_t *src, size_t len, const char **err_desc)
{
    for (; len >= 6; len -= 6, src += 6) {
        uint16_t identifier = h2o_http2_decode16u(src);
        uint32_t value = h2o_http2_decode32u(src + 2);
        switch (identifier) {
#define SET(label, member, min, max, err_code)                                                                                     \
    case H2O_HTTP2_SETTINGS_##label:                                                                                               \
        if (!(min <= value && value <= max)) {                                                                                     \
            *err_desc = "invalid SETTINGS frame";                                                                                  \
            return err_code;                                                                                                       \
        }                                                                                                                          \
        settings->member = value;                                                                                                  \
        break
            SET(HEADER_TABLE_SIZE, header_table_size, 0, UINT32_MAX, 0);
            SET(ENABLE_PUSH, enable_push, 0, 1, H2O_HTTP2_ERROR_PROTOCOL);
            SET(MAX_CONCURRENT_STREAMS, max_concurrent_streams, 0, UINT32_MAX, 0);
            SET(INITIAL_WINDOW_SIZE, initial_window_size, 0, 0x7fffffff, H2O_HTTP2_ERROR_FLOW_CONTROL);
            SET(MAX_FRAME_SIZE, max_frame_size, 16384, 16777215, H2O_HTTP2_ERROR_PROTOCOL);
#undef SET
        default:
            /* ignore unknown (5.5) */
            break;
        }
    }

    if (len != 0)
        return H2O_HTTP2_ERROR_FRAME_SIZE;
    return 0;
}