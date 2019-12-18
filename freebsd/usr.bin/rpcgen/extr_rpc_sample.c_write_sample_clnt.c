#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_3__ version_list ;
struct TYPE_7__ {TYPE_3__* versions; } ;
struct TYPE_8__ {TYPE_1__ pr; } ;
struct TYPE_10__ {scalar_t__ def_kind; int /*<<< orphan*/  def_name; TYPE_2__ def; } ;
typedef  TYPE_4__ definition ;

/* Variables and functions */
 scalar_t__ DEF_PROGRAM ; 
 int /*<<< orphan*/  write_sample_client (int /*<<< orphan*/ ,TYPE_3__*) ; 

int
write_sample_clnt(definition *def)
{
        version_list *vp;
	int count = 0;

	if (def->def_kind != DEF_PROGRAM)
	  return(0);
	/* generate sample code for each version */
	for (vp = def->def.pr.versions; vp != NULL; vp = vp->next) {
	  write_sample_client(def->def_name, vp);
	  ++count;
	}
	return(count);
}