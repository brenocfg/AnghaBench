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
typedef  int /*<<< orphan*/  u16 ;
struct property_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void const*) ; 
 int PTR_ERR (void const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 void* property_entry_find (struct property_entry const*,char const*,size_t) ; 

__attribute__((used)) static int property_entry_read_u16_array(const struct property_entry *props,
					 const char *propname,
					 u16 *values, size_t nval)
{
	const void *pointer;
	size_t length = nval * sizeof(*values);

	pointer = property_entry_find(props, propname, length);
	if (IS_ERR(pointer))
		return PTR_ERR(pointer);

	memcpy(values, pointer, length);
	return 0;
}