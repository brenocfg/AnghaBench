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
typedef  int OM_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_KRB5_MECHANISM ; 
 int GSS_S_COMPLETE ; 
 int /*<<< orphan*/  _gsskrb5_encap_length (size_t,size_t*,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
sub_wrap_size (
            OM_uint32 req_output_size,
            OM_uint32 * max_input_size,
	    int blocksize,
	    int extrasize
           )
{
    size_t len, total_len;

    len = 8 + req_output_size + blocksize + extrasize;

    _gsskrb5_encap_length(len, &len, &total_len, GSS_KRB5_MECHANISM);

    total_len -= req_output_size; /* token length */
    if (total_len < req_output_size) {
        *max_input_size = (req_output_size - total_len);
        (*max_input_size) &= (~(OM_uint32)(blocksize - 1));
    } else {
        *max_input_size = 0;
    }
    return GSS_S_COMPLETE;
}