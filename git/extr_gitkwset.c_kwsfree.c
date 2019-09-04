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
struct kwset {int /*<<< orphan*/  obstack; } ;
typedef  scalar_t__ kwset_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
kwsfree (kwset_t kws)
{
  struct kwset *kwset;

  kwset = (struct kwset *) kws;
  obstack_free(&kwset->obstack, NULL);
  free(kws);
}