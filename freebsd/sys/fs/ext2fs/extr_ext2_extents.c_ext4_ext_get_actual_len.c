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
typedef  scalar_t__ uint16_t ;
struct ext4_extent {scalar_t__ e_len; } ;

/* Variables and functions */
 scalar_t__ EXT_INIT_MAX_LEN ; 

__attribute__((used)) static inline uint16_t
ext4_ext_get_actual_len(struct ext4_extent *ext)
{

	return (ext->e_len <= EXT_INIT_MAX_LEN ?
	    ext->e_len : (ext->e_len - EXT_INIT_MAX_LEN));
}