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
typedef  int u64 ;
typedef  int limb ;
typedef  int* largefelem ;
typedef  int* felem ;

/* Variables and functions */
 int bottom52bits ; 
 int bottom58bits ; 

__attribute__((used)) static void felem_reduce(felem out, const largefelem in)
{
    u64 overflow1, overflow2;

    out[0] = ((limb) in[0]) & bottom58bits;
    out[1] = ((limb) in[1]) & bottom58bits;
    out[2] = ((limb) in[2]) & bottom58bits;
    out[3] = ((limb) in[3]) & bottom58bits;
    out[4] = ((limb) in[4]) & bottom58bits;
    out[5] = ((limb) in[5]) & bottom58bits;
    out[6] = ((limb) in[6]) & bottom58bits;
    out[7] = ((limb) in[7]) & bottom58bits;
    out[8] = ((limb) in[8]) & bottom58bits;

    /* out[i] < 2^58 */

    out[1] += ((limb) in[0]) >> 58;
    out[1] += (((limb) (in[0] >> 64)) & bottom52bits) << 6;
    /*-
     * out[1] < 2^58 + 2^6 + 2^58
     *        = 2^59 + 2^6
     */
    out[2] += ((limb) (in[0] >> 64)) >> 52;

    out[2] += ((limb) in[1]) >> 58;
    out[2] += (((limb) (in[1] >> 64)) & bottom52bits) << 6;
    out[3] += ((limb) (in[1] >> 64)) >> 52;

    out[3] += ((limb) in[2]) >> 58;
    out[3] += (((limb) (in[2] >> 64)) & bottom52bits) << 6;
    out[4] += ((limb) (in[2] >> 64)) >> 52;

    out[4] += ((limb) in[3]) >> 58;
    out[4] += (((limb) (in[3] >> 64)) & bottom52bits) << 6;
    out[5] += ((limb) (in[3] >> 64)) >> 52;

    out[5] += ((limb) in[4]) >> 58;
    out[5] += (((limb) (in[4] >> 64)) & bottom52bits) << 6;
    out[6] += ((limb) (in[4] >> 64)) >> 52;

    out[6] += ((limb) in[5]) >> 58;
    out[6] += (((limb) (in[5] >> 64)) & bottom52bits) << 6;
    out[7] += ((limb) (in[5] >> 64)) >> 52;

    out[7] += ((limb) in[6]) >> 58;
    out[7] += (((limb) (in[6] >> 64)) & bottom52bits) << 6;
    out[8] += ((limb) (in[6] >> 64)) >> 52;

    out[8] += ((limb) in[7]) >> 58;
    out[8] += (((limb) (in[7] >> 64)) & bottom52bits) << 6;
    /*-
     * out[x > 1] < 2^58 + 2^6 + 2^58 + 2^12
     *            < 2^59 + 2^13
     */
    overflow1 = ((limb) (in[7] >> 64)) >> 52;

    overflow1 += ((limb) in[8]) >> 58;
    overflow1 += (((limb) (in[8] >> 64)) & bottom52bits) << 6;
    overflow2 = ((limb) (in[8] >> 64)) >> 52;

    overflow1 <<= 1;            /* overflow1 < 2^13 + 2^7 + 2^59 */
    overflow2 <<= 1;            /* overflow2 < 2^13 */

    out[0] += overflow1;        /* out[0] < 2^60 */
    out[1] += overflow2;        /* out[1] < 2^59 + 2^6 + 2^13 */

    out[1] += out[0] >> 58;
    out[0] &= bottom58bits;
    /*-
     * out[0] < 2^58
     * out[1] < 2^59 + 2^6 + 2^13 + 2^2
     *        < 2^59 + 2^14
     */
}