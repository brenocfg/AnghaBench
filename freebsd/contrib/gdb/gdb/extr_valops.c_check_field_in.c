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
struct type {int dummy; } ;

/* Variables and functions */
 struct type* TYPE_BASECLASS (struct type*,int) ; 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 char* TYPE_FN_FIELDLIST_NAME (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int TYPE_NFN_FIELDS (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 scalar_t__ destructor_name_p (char const*,struct type*) ; 
 int get_destructor_fn_field (struct type*,int*,int*) ; 
 scalar_t__ strcmp_iw (char*,char const*) ; 

__attribute__((used)) static int
check_field_in (struct type *type, const char *name)
{
  int i;

  for (i = TYPE_NFIELDS (type) - 1; i >= TYPE_N_BASECLASSES (type); i--)
    {
      char *t_field_name = TYPE_FIELD_NAME (type, i);
      if (t_field_name && (strcmp_iw (t_field_name, name) == 0))
	return 1;
    }

  /* C++: If it was not found as a data field, then try to
     return it as a pointer to a method.  */

  /* Destructors are a special case.  */
  if (destructor_name_p (name, type))
    {
      int m_index, f_index;

      return get_destructor_fn_field (type, &m_index, &f_index);
    }

  for (i = TYPE_NFN_FIELDS (type) - 1; i >= 0; --i)
    {
      if (strcmp_iw (TYPE_FN_FIELDLIST_NAME (type, i), name) == 0)
	return 1;
    }

  for (i = TYPE_N_BASECLASSES (type) - 1; i >= 0; i--)
    if (check_field_in (TYPE_BASECLASS (type, i), name))
      return 1;

  return 0;
}