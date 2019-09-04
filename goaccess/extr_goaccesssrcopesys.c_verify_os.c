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
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  OPESYS_TYPE_LEN ; 
 char* alloc_string (char*) ; 
 int /*<<< orphan*/ ** os ; 
 char* parse_os (char const*,char*,char*,size_t) ; 
 char* strstr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrncpy (char*,char*,int /*<<< orphan*/ ) ; 

char *
verify_os (const char *str, char *os_type)
{
  char *a;
  size_t i;

  if (str == NULL || *str == '\0')
    return NULL;

  for (i = 0; i < ARRAY_SIZE (os); i++) {
    if ((a = strstr (str, os[i][0])) != NULL)
      return parse_os (str, a, os_type, i);
  }
  xstrncpy (os_type, "Unknown", OPESYS_TYPE_LEN);

  return alloc_string ("Unknown");
}