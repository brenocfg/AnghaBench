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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_set_lyr_2_4 ; 
 int /*<<< orphan*/  ip_protocol ; 

__attribute__((used)) static void set_proto(void *outer_c, void *outer_v, u8 mask, u8 val)
{
	MLX5_SET(fte_match_set_lyr_2_4, outer_c, ip_protocol, mask);
	MLX5_SET(fte_match_set_lyr_2_4, outer_v, ip_protocol, val);
}