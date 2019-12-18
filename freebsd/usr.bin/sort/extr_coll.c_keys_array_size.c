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
struct key_value {int dummy; } ;

/* Variables and functions */
 int key_hint_size () ; 
 int keys_num ; 

size_t
keys_array_size(void)
{

	return (keys_num * (sizeof(struct key_value) + key_hint_size()));
}