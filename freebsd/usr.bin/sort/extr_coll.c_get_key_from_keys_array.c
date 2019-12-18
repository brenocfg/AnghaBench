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
struct keys_array {scalar_t__ key; } ;
struct key_value {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int key_hint_size () ; 

struct key_value *
get_key_from_keys_array(struct keys_array *ka, size_t ind)
{

	return ((struct key_value *)((caddr_t)ka->key +
	    ind * (sizeof(struct key_value) + key_hint_size())));
}