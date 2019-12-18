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
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ENUM 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 char* TYPE_NAME (struct type*) ; 
 char* TYPE_TAG_NAME (struct type*) ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  symfile_complaints ; 

__attribute__((used)) static void 
complain_about_struct_wipeout (struct type *type)
{
  char *name = "";
  char *kind = "";

  if (TYPE_TAG_NAME (type))
    {
      name = TYPE_TAG_NAME (type);
      switch (TYPE_CODE (type))
        {
        case TYPE_CODE_STRUCT: kind = "struct "; break;
        case TYPE_CODE_UNION:  kind = "union ";  break;
        case TYPE_CODE_ENUM:   kind = "enum ";   break;
        default: kind = "";
        }
    }
  else if (TYPE_NAME (type))
    {
      name = TYPE_NAME (type);
      kind = "";
    }
  else
    {
      name = "<unknown>";
      kind = "";
    }

  complaint (&symfile_complaints,
	     "struct/union type gets multiply defined: %s%s", kind, name);
}