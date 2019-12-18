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
 unsigned int SIZEOF_ARRAY (char const**) ; 
 char const** class_names ; 

const char *
der_get_class_name(unsigned num)
{
    if (num >= SIZEOF_ARRAY(class_names))
	return NULL;
    return class_names[num];
}