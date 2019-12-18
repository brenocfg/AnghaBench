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
 scalar_t__ const l_base ; 
 scalar_t__ const l_count ; 
 scalar_t__ s_base ; 
 scalar_t__ s_count ; 
 scalar_t__ const t_base ; 
 unsigned int t_count ; 
 scalar_t__ const v_base ; 
 unsigned int v_count ; 

__attribute__((used)) static uint32_t
hangul_composition(const uint32_t *in, size_t in_len)
{
    if (in_len < 2)
	return 0;
    if (in[0] >= l_base && in[0] < l_base + l_count) {
	unsigned l_index = in[0] - l_base;
	unsigned v_index;

	if (in[1] < v_base || in[1] >= v_base + v_count)
	    return 0;
	v_index = in[1] - v_base;
	return (l_index * v_count + v_index) * t_count + s_base;
    } else if (in[0] >= s_base && in[0] < s_base + s_count) {
	unsigned s_index = in[0] - s_base;
	unsigned t_index;

	if (s_index % t_count != 0)
	    return 0;
	if (in[1] < t_base || in[1] >= t_base + t_count)
	    return 0;
	t_index = in[1] - t_base;
	return in[0] + t_index;
    }
    return 0;
}