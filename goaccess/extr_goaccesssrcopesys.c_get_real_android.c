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
 char* alloc_string (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static char *
get_real_android (const char *droid)
{
  if (strstr (droid, "9"))
    return alloc_string ("Pie 9");
  else if (strstr (droid, "8.1"))
    return alloc_string ("Oreo 8.1");
  else if (strstr (droid, "8.0"))
    return alloc_string ("Oreo 8.0");
  else if (strstr (droid, "7.1"))
    return alloc_string ("Nougat 7.1");
  else if (strstr (droid, "7.0"))
    return alloc_string ("Nougat 7.0");
  else if (strstr (droid, "6.0.1"))
    return alloc_string ("Marshmallow 6.0.1");
  else if (strstr (droid, "6.0"))
    return alloc_string ("Marshmallow 6.0");
  else if (strstr (droid, "5.1"))
    return alloc_string ("Lollipop 5.1");
  else if (strstr (droid, "5.0"))
    return alloc_string ("Lollipop 5.0");
  else if (strstr (droid, "4.4"))
    return alloc_string ("KitKat 4.4");
  else if (strstr (droid, "4.3"))
    return alloc_string ("Jelly Bean 4.3");
  else if (strstr (droid, "4.2"))
    return alloc_string ("Jelly Bean 4.2");
  else if (strstr (droid, "4.1"))
    return alloc_string ("Jelly Bean 4.1");
  else if (strstr (droid, "4.0"))
    return alloc_string ("Ice Cream Sandwich 4.0");
  else if (strstr (droid, "3."))
    return alloc_string ("Honeycomb 3");
  else if (strstr (droid, "2.3"))
    return alloc_string ("Gingerbread 2.3");
  else if (strstr (droid, "2.2"))
    return alloc_string ("Froyo 2.2");
  else if (strstr (droid, "2.0") || strstr (droid, "2.1"))
    return alloc_string ("Eclair 2");
  else if (strstr (droid, "1.6"))
    return alloc_string ("Donut 1.6");
  else if (strstr (droid, "1.5"))
    return alloc_string ("Cupcake 1.5");
  return alloc_string (droid);
}