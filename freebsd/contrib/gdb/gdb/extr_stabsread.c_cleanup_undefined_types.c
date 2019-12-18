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
struct symbol {int dummy; } ;
struct pending {int nsyms; struct symbol** symbol; struct pending* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 int /*<<< orphan*/  LOC_TYPEDEF ; 
 int /*<<< orphan*/  STRUCT_DOMAIN ; 
 int /*<<< orphan*/  SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_DOMAIN (struct symbol*) ; 
 struct type* SYMBOL_TYPE (struct symbol*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ENUM 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 int /*<<< orphan*/  TYPE_STUB (struct type*) ; 
 char* TYPE_TAG_NAME (struct type*) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,...) ; 
 struct pending* file_symbols ; 
 int /*<<< orphan*/  replace_type (struct type*,struct type*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 struct type** undef_types ; 
 int undef_types_length ; 

void
cleanup_undefined_types (void)
{
  struct type **type;

  for (type = undef_types; type < undef_types + undef_types_length; type++)
    {
      switch (TYPE_CODE (*type))
	{

	case TYPE_CODE_STRUCT:
	case TYPE_CODE_UNION:
	case TYPE_CODE_ENUM:
	  {
	    /* Check if it has been defined since.  Need to do this here
	       as well as in check_typedef to deal with the (legitimate in
	       C though not C++) case of several types with the same name
	       in different source files.  */
	    if (TYPE_STUB (*type))
	      {
		struct pending *ppt;
		int i;
		/* Name of the type, without "struct" or "union" */
		char *typename = TYPE_TAG_NAME (*type);

		if (typename == NULL)
		  {
		    complaint (&symfile_complaints, "need a type name");
		    break;
		  }
		for (ppt = file_symbols; ppt; ppt = ppt->next)
		  {
		    for (i = 0; i < ppt->nsyms; i++)
		      {
			struct symbol *sym = ppt->symbol[i];

			if (SYMBOL_CLASS (sym) == LOC_TYPEDEF
			    && SYMBOL_DOMAIN (sym) == STRUCT_DOMAIN
			    && (TYPE_CODE (SYMBOL_TYPE (sym)) ==
				TYPE_CODE (*type))
			    && strcmp (DEPRECATED_SYMBOL_NAME (sym), typename) == 0)
                          replace_type (*type, SYMBOL_TYPE (sym));
		      }
		  }
	      }
	  }
	  break;

	default:
	  {
	    complaint (&symfile_complaints,
		       "forward-referenced types left unresolved, "
                       "type code %d.",
		       TYPE_CODE (*type));
	  }
	  break;
	}
    }

  undef_types_length = 0;
}