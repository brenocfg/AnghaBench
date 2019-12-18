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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int WIND_ERR_OVERRUN ; 
 unsigned int l_base ; 
 unsigned int n_count ; 
 scalar_t__ s_base ; 
 scalar_t__ s_count ; 
 unsigned int t_base ; 
 unsigned int t_count ; 
 unsigned int v_base ; 

__attribute__((used)) static int
hangul_decomp(const uint32_t *in, size_t in_len,
	      uint32_t *out, size_t *out_len)
{
    uint32_t u = *in;
    unsigned s_index;
    unsigned l, v, t;
    unsigned o;

    if (u < s_base || u >= s_base + s_count)
	return 0;
    s_index = u - s_base;
    l = l_base + s_index / n_count;
    v = v_base + (s_index % n_count) / t_count;
    t = t_base + s_index % t_count;
    o = 2;
    if (t != t_base)
	++o;
    if (*out_len < o)
	return WIND_ERR_OVERRUN;
    out[0] = l;
    out[1] = v;
    if (t != t_base)
	out[2] = t;
    *out_len = o;
    return 1;
}