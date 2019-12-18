#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int next_data_empty; int bytes_hashed; scalar_t__ state; scalar_t__ data; } ;
typedef  TYPE_1__ nh_ctx ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT64 ;

/* Variables and functions */
 int L1_PAD_BOUNDARY ; 
 int /*<<< orphan*/  nh_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  nh_transform (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  zero_pad (scalar_t__,int) ; 

__attribute__((used)) static void nh_final(nh_ctx *hc, UINT8 *result)
/* After passing some number of data buffers to nh_update() for integration
 * into an NH context, nh_final is called to produce a hash result. If any
 * bytes are in the buffer hc->data, incorporate them into the
 * NH context. Finally, add into the NH accumulation "state" the total number
 * of bits hashed. The resulting numbers are written to the buffer "result".
 * If nh_update was never called, L1_PAD_BOUNDARY zeroes are incorporated.
 */
{
    int nh_len, nbits;

    if (hc->next_data_empty != 0) {
        nh_len = ((hc->next_data_empty + (L1_PAD_BOUNDARY - 1)) &
                                                ~(L1_PAD_BOUNDARY - 1));
        zero_pad(hc->data + hc->next_data_empty,
                                          nh_len - hc->next_data_empty);
        nh_transform(hc, hc->data, nh_len);
        hc->bytes_hashed += hc->next_data_empty;
    } else if (hc->bytes_hashed == 0) {
	nh_len = L1_PAD_BOUNDARY;
        zero_pad(hc->data, L1_PAD_BOUNDARY);
        nh_transform(hc, hc->data, nh_len);
    }

    nbits = (hc->bytes_hashed << 3);
    ((UINT64 *)result)[0] = ((UINT64 *)hc->state)[0] + nbits;
#if (UMAC_OUTPUT_LEN >= 8)
    ((UINT64 *)result)[1] = ((UINT64 *)hc->state)[1] + nbits;
#endif
#if (UMAC_OUTPUT_LEN >= 12)
    ((UINT64 *)result)[2] = ((UINT64 *)hc->state)[2] + nbits;
#endif
#if (UMAC_OUTPUT_LEN == 16)
    ((UINT64 *)result)[3] = ((UINT64 *)hc->state)[3] + nbits;
#endif
    nh_reset(hc);
}