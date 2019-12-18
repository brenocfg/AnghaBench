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
struct objfile {int dummy; } ;
struct nextfield {struct nextfield* next; } ;
struct field_info {struct nextfield* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  STABS_CONTINUE (char**,struct objfile*) ; 
 scalar_t__ is_cplus_marker (char) ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,struct nextfield*) ; 
 int /*<<< orphan*/  memset (struct nextfield*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_cpp_abbrev (struct field_info*,char**,struct type*,struct objfile*) ; 
 int /*<<< orphan*/  read_one_struct_field (struct field_info*,char**,char*,struct type*,struct objfile*) ; 
 int /*<<< orphan*/  xfree ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static int
read_struct_fields (struct field_info *fip, char **pp, struct type *type,
		    struct objfile *objfile)
{
  char *p;
  struct nextfield *new;

  /* We better set p right now, in case there are no fields at all...    */

  p = *pp;

  /* Read each data member type until we find the terminating ';' at the end of
     the data member list, or break for some other reason such as finding the
     start of the member function list. */
  /* Stab string for structure/union does not end with two ';' in
     SUN C compiler 5.3 i.e. F6U2, hence check for end of string. */

  while (**pp != ';' && **pp != '\0')
    {
      STABS_CONTINUE (pp, objfile);
      /* Get space to record the next field's data.  */
      new = (struct nextfield *) xmalloc (sizeof (struct nextfield));
      make_cleanup (xfree, new);
      memset (new, 0, sizeof (struct nextfield));
      new->next = fip->list;
      fip->list = new;

      /* Get the field name.  */
      p = *pp;

      /* If is starts with CPLUS_MARKER it is a special abbreviation,
         unless the CPLUS_MARKER is followed by an underscore, in
         which case it is just the name of an anonymous type, which we
         should handle like any other type name.  */

      if (is_cplus_marker (p[0]) && p[1] != '_')
	{
	  if (!read_cpp_abbrev (fip, pp, type, objfile))
	    return 0;
	  continue;
	}

      /* Look for the ':' that separates the field name from the field
         values.  Data members are delimited by a single ':', while member
         functions are delimited by a pair of ':'s.  When we hit the member
         functions (if any), terminate scan loop and return. */

      while (*p != ':' && *p != '\0')
	{
	  p++;
	}
      if (*p == '\0')
	return 0;

      /* Check to see if we have hit the member functions yet.  */
      if (p[1] == ':')
	{
	  break;
	}
      read_one_struct_field (fip, pp, p, type, objfile);
    }
  if (p[0] == ':' && p[1] == ':')
    {
      /* (the deleted) chill the list of fields: the last entry (at
         the head) is a partially constructed entry which we now
         scrub. */
      fip->list = fip->list->next;
    }
  return 1;
}