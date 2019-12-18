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
struct loop_info64 {scalar_t__ lo_encrypt_key_size; } ;
struct loop_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int xor_init(struct loop_device *lo, const struct loop_info64 *info)
{
	if (unlikely(info->lo_encrypt_key_size <= 0))
		return -EINVAL;
	return 0;
}