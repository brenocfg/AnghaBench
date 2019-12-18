#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct objfile {int /*<<< orphan*/  objfile_obstack; } ;
struct TYPE_3__ {int /*<<< orphan*/  nsyms; } ;

/* Variables and functions */
 TYPE_1__* common_block ; 
 int /*<<< orphan*/  common_block_i ; 
 int /*<<< orphan*/ * common_block_name ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* local_symbols ; 
 int /*<<< orphan*/ * obsavestring (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  symfile_complaints ; 

void
common_block_start (char *name, struct objfile *objfile)
{
  if (common_block_name != NULL)
    {
      complaint (&symfile_complaints,
		 "Invalid symbol data: common block within common block");
    }
  common_block = local_symbols;
  common_block_i = local_symbols ? local_symbols->nsyms : 0;
  common_block_name = obsavestring (name, strlen (name),
				    &objfile->objfile_obstack);
}