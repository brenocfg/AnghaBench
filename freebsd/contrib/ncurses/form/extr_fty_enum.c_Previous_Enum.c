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
struct TYPE_2__ {int count; char** kwds; int checkcase; } ;
typedef  TYPE_1__ enumARG ;
typedef  int /*<<< orphan*/  FIELD ;

/* Variables and functions */
 scalar_t__ Compare (unsigned char const*,unsigned char*,int) ; 
 scalar_t__ EXACT ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ dummy ; 
 scalar_t__ field_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_field_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
Previous_Enum(FIELD *field, const void *argp)
{
  const enumARG *args = (const enumARG *)argp;
  int cnt = args->count;
  char **kwds = &args->kwds[cnt - 1];
  bool ccase = args->checkcase;
  unsigned char *bp = (unsigned char *)field_buffer(field, 0);

  if (kwds)
    {
      while (cnt--)
	{
	  if (Compare((unsigned char *)(*kwds--), bp, ccase) == EXACT)
	    break;
	}

      if (cnt <= 0)
	kwds = &args->kwds[args->count - 1];

      if ((cnt >= 0) || (Compare((const unsigned char *)dummy, bp, ccase) == EXACT))
	{
	  set_field_buffer(field, 0, *kwds);
	  return TRUE;
	}
    }
  return FALSE;
}