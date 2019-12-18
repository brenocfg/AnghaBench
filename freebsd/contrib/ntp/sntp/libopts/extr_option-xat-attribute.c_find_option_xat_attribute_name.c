#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* xat_name; } ;
typedef  TYPE_1__ option_xat_attribute_map_t ;

/* Variables and functions */
 scalar_t__ option_xat_attribute_hash (char const*,unsigned int) ; 
 TYPE_1__ const* option_xat_attribute_table ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,unsigned int) ; 

__attribute__((used)) static inline const option_xat_attribute_map_t *
find_option_xat_attribute_name (register const char *str, register unsigned int len)
{
  if (len <= 8 && len >= 4)
    {
      register int key = (int)option_xat_attribute_hash (str, len);

      if (key <= 9 && key >= 0)
        {
          register const char *s = option_xat_attribute_table[key].xat_name;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &option_xat_attribute_table[key];
        }
    }
  return 0;
}