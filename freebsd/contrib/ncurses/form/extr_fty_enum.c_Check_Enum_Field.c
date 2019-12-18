#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char** kwds; int checkcase; int checkunique; } ;
typedef  TYPE_1__ enumARG ;
typedef  int /*<<< orphan*/  FIELD ;

/* Variables and functions */
 int Compare (unsigned char*,unsigned char*,int) ; 
 int EXACT ; 
 int FALSE ; 
 int NOMATCH ; 
 int TRUE ; 
 scalar_t__ field_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_field_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
Check_Enum_Field(FIELD *field, const void *argp)
{
  char **kwds = ((const enumARG *)argp)->kwds;
  bool ccase = ((const enumARG *)argp)->checkcase;
  bool unique = ((const enumARG *)argp)->checkunique;
  unsigned char *bp = (unsigned char *)field_buffer(field, 0);
  char *s, *t, *p;
  int res;

  while (kwds && (s = (*kwds++)))
    {
      if ((res = Compare((unsigned char *)s, bp, ccase)) != NOMATCH)
	{
	  p = t = s;		/* t is at least a partial match */
	  if ((unique && res != EXACT))
	    {
	      while (kwds && (p = *kwds++))
		{
		  if ((res = Compare((unsigned char *)p, bp, ccase)) != NOMATCH)
		    {
		      if (res == EXACT)
			{
			  t = p;
			  break;
			}
		      else
			t = (char *)0;
		    }
		}
	    }
	  if (t)
	    {
	      set_field_buffer(field, 0, t);
	      return TRUE;
	    }
	  if (!p)
	    break;
	}
    }
  return FALSE;
}