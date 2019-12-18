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
struct TYPE_2__ {int /*<<< orphan*/ ******* iconfigfile; } ;

/* Variables and functions */
 TYPE_1__ conf ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *****) ; 
 int nargc ; 
 int /*<<< orphan*/ ***** nargv ; 

void
free_cmd_args (void)
{
  int i;
  if (nargc == 0)
    return;
  for (i = 0; i < nargc; i++)
    free (nargv[i]);
  free (nargv);
  free (conf.iconfigfile);
}