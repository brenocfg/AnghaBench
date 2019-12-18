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
struct ui_file {int dummy; } ;
typedef  enum val_prettyprint { ____Placeholder_val_prettyprint } val_prettyprint ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  SCM_CAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCM_CDR (int /*<<< orphan*/ ) ; 
 scalar_t__ SCM_NECONSP (int /*<<< orphan*/ ) ; 
 scalar_t__ SCM_NIMP (int /*<<< orphan*/ ) ; 
 scalar_t__ SCM_NNULLP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 unsigned int print_max ; 
 int /*<<< orphan*/  scm_scmval_print (int /*<<< orphan*/ ,struct ui_file*,int,int,int,int) ; 

__attribute__((used)) static void
scm_scmlist_print (LONGEST svalue, struct ui_file *stream, int format,
		   int deref_ref, int recurse, enum val_prettyprint pretty)
{
  unsigned int more = print_max;
  if (recurse > 6)
    {
      fputs_filtered ("...", stream);
      return;
    }
  scm_scmval_print (SCM_CAR (svalue), stream, format,
		    deref_ref, recurse + 1, pretty);
  svalue = SCM_CDR (svalue);
  for (; SCM_NIMP (svalue); svalue = SCM_CDR (svalue))
    {
      if (SCM_NECONSP (svalue))
	break;
      fputs_filtered (" ", stream);
      if (--more == 0)
	{
	  fputs_filtered ("...", stream);
	  return;
	}
      scm_scmval_print (SCM_CAR (svalue), stream, format,
			deref_ref, recurse + 1, pretty);
    }
  if (SCM_NNULLP (svalue))
    {
      fputs_filtered (" . ", stream);
      scm_scmval_print (svalue, stream, format,
			deref_ref, recurse + 1, pretty);
    }
}