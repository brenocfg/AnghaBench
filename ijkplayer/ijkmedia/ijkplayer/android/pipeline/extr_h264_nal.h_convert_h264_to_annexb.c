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
typedef  int uint8_t ;
struct TYPE_3__ {size_t nal_pos; int nal_len; } ;
typedef  TYPE_1__ H264ConvertState ;

/* Variables and functions */
 int INT_MAX ; 

__attribute__((used)) static void convert_h264_to_annexb( uint8_t *p_buf, size_t i_len,
                                    size_t i_nal_size,
                                    H264ConvertState *state )
{
    if( i_nal_size < 3 || i_nal_size > 4 )
        return;

    /* This only works for NAL sizes 3-4 */
    while( i_len > 0 )
    {
        if( state->nal_pos < i_nal_size ) {
            unsigned int i;
            for( i = 0; state->nal_pos < i_nal_size && i < i_len; i++, state->nal_pos++ ) {
                state->nal_len = (state->nal_len << 8) | p_buf[i];
                p_buf[i] = 0;
            }
            if( state->nal_pos < i_nal_size )
                return;
            p_buf[i - 1] = 1;
            p_buf += i;
            i_len -= i;
        }
        if( state->nal_len > INT_MAX )
            return;
        if( state->nal_len > i_len )
        {
            state->nal_len -= i_len;
            return;
        }
        else
        {
            p_buf += state->nal_len;
            i_len -= state->nal_len;
            state->nal_len = 0;
            state->nal_pos = 0;
        }
    }
}