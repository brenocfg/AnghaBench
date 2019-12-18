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
struct varobj {int name; } ;
struct type {int dummy; } ;

/* Variables and functions */
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 131 
#define  TYPE_CODE_PTR 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 char* TYPE_FIELD_NAME (struct type*,int) ; 
 struct type* get_target_type (struct type*) ; 
 struct type* get_type (struct varobj*) ; 
 char* savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static char *
c_name_of_child (struct varobj *parent, int index)
{
  struct type *type;
  struct type *target;
  char *name;
  char *string;

  type = get_type (parent);
  target = get_target_type (type);

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_ARRAY:
      xasprintf (&name, "%d", index);
      break;

    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
      string = TYPE_FIELD_NAME (type, index);
      name = savestring (string, strlen (string));
      break;

    case TYPE_CODE_PTR:
      switch (TYPE_CODE (target))
	{
	case TYPE_CODE_STRUCT:
	case TYPE_CODE_UNION:
	  string = TYPE_FIELD_NAME (target, index);
	  name = savestring (string, strlen (string));
	  break;

	default:
	  xasprintf (&name, "*%s", parent->name);
	  break;
	}
      break;

    default:
      /* This should not happen */
      name = xstrdup ("???");
    }

  return name;
}