#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {struct TYPE_16__* right; struct TYPE_16__* left; } ;
typedef  TYPE_2__ TypeArgument ;
struct TYPE_18__ {TYPE_2__* buf; scalar_t__ opts; } ;
struct TYPE_15__ {int (* ofcheck ) (TYPE_5__*,void*) ;int (* gfcheck ) (int /*<<< orphan*/ *,TYPE_5__*,void*) ;} ;
struct TYPE_17__ {int status; int (* fcheck ) (TYPE_5__*,void*) ;TYPE_1__ fieldcheck; struct TYPE_17__* right; struct TYPE_17__* left; } ;
typedef  int /*<<< orphan*/  FORM ;
typedef  TYPE_2__ FIELD_CELL ;
typedef  TYPE_4__ FIELDTYPE ;
typedef  TYPE_5__ FIELD ;

/* Variables and functions */
 scalar_t__ CharOf (TYPE_2__) ; 
 scalar_t__ ISBLANK (TYPE_2__) ; 
 unsigned int O_NULLOK ; 
 int TRUE ; 
 int _GENERIC ; 
 int _LINKED_TYPE ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_5__*,void*) ; 
 int stub2 (TYPE_5__*,void*) ; 
 int stub3 (TYPE_5__*,void*) ; 

__attribute__((used)) static bool
Check_Field(FORM *form, FIELDTYPE *typ, FIELD *field, TypeArgument *argp)
{
  if (typ)
    {
      if ((unsigned)field->opts & O_NULLOK)
	{
	  FIELD_CELL *bp = field->buf;

	  assert(bp);
	  while (ISBLANK(*bp))
	    {
	      bp++;
	    }
	  if (CharOf(*bp) == 0)
	    return TRUE;
	}

      if (typ->status & _LINKED_TYPE)
	{
	  assert(argp);
	  return (
		   Check_Field(form, typ->left, field, argp->left) ||
		   Check_Field(form, typ->right, field, argp->right));
	}
      else
	{
#if NCURSES_INTEROP_FUNCS
	  if (typ->fieldcheck.ofcheck)
	    {
	      if (typ->status & _GENERIC)
		return typ->fieldcheck.gfcheck(form, field, (void *)argp);
	      else
		return typ->fieldcheck.ofcheck(field, (void *)argp);
	    }
#else
	  if (typ->fcheck)
	    return typ->fcheck(field, (void *)argp);
#endif
	}
    }
  return TRUE;
}