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
struct varobj {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ CPLUS_FAKE_CHILD (struct varobj*) ; 
 int TYPE_CODE (struct type*) ; 
#define  TYPE_CODE_ARRAY 130 
#define  TYPE_CODE_STRUCT 129 
#define  TYPE_CODE_UNION 128 
 struct type* get_type (struct varobj*) ; 

__attribute__((used)) static int
type_changeable (struct varobj *var)
{
  int r;
  struct type *type;

  if (CPLUS_FAKE_CHILD (var))
    return 0;

  type = get_type (var);

  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
    case TYPE_CODE_ARRAY:
      r = 0;
      break;

    default:
      r = 1;
    }

  return r;
}