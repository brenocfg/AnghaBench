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
struct target_ops {int /*<<< orphan*/  to_doc; int /*<<< orphan*/  to_open; int /*<<< orphan*/  to_shortname; int /*<<< orphan*/ * to_xfer_partial; } ;

/* Variables and functions */
 int DEFAULT_ALLOCSIZE ; 
 int /*<<< orphan*/  add_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_run ; 
 int /*<<< orphan*/  cmdlist ; 
 int /*<<< orphan*/ * default_xfer_partial ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  target_command ; 
 int target_struct_allocsize ; 
 int target_struct_size ; 
 struct target_ops** target_structs ; 
 int /*<<< orphan*/ * targetlist ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

void
add_target (struct target_ops *t)
{
  /* Provide default values for all "must have" methods.  */
  if (t->to_xfer_partial == NULL)
    t->to_xfer_partial = default_xfer_partial;

  if (!target_structs)
    {
      target_struct_allocsize = DEFAULT_ALLOCSIZE;
      target_structs = (struct target_ops **) xmalloc
	(target_struct_allocsize * sizeof (*target_structs));
    }
  if (target_struct_size >= target_struct_allocsize)
    {
      target_struct_allocsize *= 2;
      target_structs = (struct target_ops **)
	xrealloc ((char *) target_structs,
		  target_struct_allocsize * sizeof (*target_structs));
    }
  target_structs[target_struct_size++] = t;

  if (targetlist == NULL)
    add_prefix_cmd ("target", class_run, target_command,
		    "Connect to a target machine or process.\n\
The first argument is the type or protocol of the target machine.\n\
Remaining arguments are interpreted by the target protocol.  For more\n\
information on the arguments for a particular protocol, type\n\
`help target ' followed by the protocol name.",
		    &targetlist, "target ", 0, &cmdlist);
  add_cmd (t->to_shortname, no_class, t->to_open, t->to_doc, &targetlist);
}