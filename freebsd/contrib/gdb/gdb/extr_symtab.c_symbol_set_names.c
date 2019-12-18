#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct objfile {int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/ * demangled_names_hash; } ;
struct TYPE_3__ {char* demangled_name; } ;
struct TYPE_4__ {TYPE_1__ cplus_specific; } ;
struct general_symbol_info {scalar_t__ language; char* name; TYPE_2__ language_specific; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 char* JAVA_PREFIX ; 
 int JAVA_PREFIX_LEN ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  create_demangled_names_hash (struct objfile*) ; 
 scalar_t__ htab_find_slot (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ language_java ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 int strlen (char*) ; 
 char* symbol_find_demangled_name (struct general_symbol_info*,char const*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
symbol_set_names (struct general_symbol_info *gsymbol,
		  const char *linkage_name, int len, struct objfile *objfile)
{
  char **slot;
  /* A 0-terminated copy of the linkage name.  */
  const char *linkage_name_copy;
  /* A copy of the linkage name that might have a special Java prefix
     added to it, for use when looking names up in the hash table.  */
  const char *lookup_name;
  /* The length of lookup_name.  */
  int lookup_len;

  if (objfile->demangled_names_hash == NULL)
    create_demangled_names_hash (objfile);

  /* The stabs reader generally provides names that are not
     NUL-terminated; most of the other readers don't do this, so we
     can just use the given copy, unless we're in the Java case.  */
  if (gsymbol->language == language_java)
    {
      char *alloc_name;
      lookup_len = len + JAVA_PREFIX_LEN;

      alloc_name = alloca (lookup_len + 1);
      memcpy (alloc_name, JAVA_PREFIX, JAVA_PREFIX_LEN);
      memcpy (alloc_name + JAVA_PREFIX_LEN, linkage_name, len);
      alloc_name[lookup_len] = '\0';

      lookup_name = alloc_name;
      linkage_name_copy = alloc_name + JAVA_PREFIX_LEN;
    }
  else if (linkage_name[len] != '\0')
    {
      char *alloc_name;
      lookup_len = len;

      alloc_name = alloca (lookup_len + 1);
      memcpy (alloc_name, linkage_name, len);
      alloc_name[lookup_len] = '\0';

      lookup_name = alloc_name;
      linkage_name_copy = alloc_name;
    }
  else
    {
      lookup_len = len;
      lookup_name = linkage_name;
      linkage_name_copy = linkage_name;
    }

  slot = (char **) htab_find_slot (objfile->demangled_names_hash,
				   lookup_name, INSERT);

  /* If this name is not in the hash table, add it.  */
  if (*slot == NULL)
    {
      char *demangled_name = symbol_find_demangled_name (gsymbol,
							 linkage_name_copy);
      int demangled_len = demangled_name ? strlen (demangled_name) : 0;

      /* If there is a demangled name, place it right after the mangled name.
	 Otherwise, just place a second zero byte after the end of the mangled
	 name.  */
      *slot = obstack_alloc (&objfile->objfile_obstack,
			     lookup_len + demangled_len + 2);
      memcpy (*slot, lookup_name, lookup_len + 1);
      if (demangled_name != NULL)
	{
	  memcpy (*slot + lookup_len + 1, demangled_name, demangled_len + 1);
	  xfree (demangled_name);
	}
      else
	(*slot)[lookup_len + 1] = '\0';
    }

  gsymbol->name = *slot + lookup_len - len;
  if ((*slot)[lookup_len + 1] != '\0')
    gsymbol->language_specific.cplus_specific.demangled_name
      = &(*slot)[lookup_len + 1];
  else
    gsymbol->language_specific.cplus_specific.demangled_name = NULL;
}