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

/* Variables and functions */
 unsigned int TORUS_MAX_DIM ; 

__attribute__((used)) static inline
bool sl_get_use_loop_vl(unsigned sl, unsigned coord_dir)
{
	return (coord_dir < TORUS_MAX_DIM)
		? (sl >> coord_dir) & 0x1 : false;
}