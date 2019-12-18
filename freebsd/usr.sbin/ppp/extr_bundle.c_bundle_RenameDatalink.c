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
struct datalink {int /*<<< orphan*/  name; struct datalink* next; } ;
struct bundle {struct datalink* links; } ;

/* Variables and functions */
 int /*<<< orphan*/  datalink_Rename (struct datalink*,char const*) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

int
bundle_RenameDatalink(struct bundle *bundle, struct datalink *ndl,
                      const char *name)
{
  struct datalink *dl;

  if (!strcasecmp(ndl->name, name))
    return 1;

  for (dl = bundle->links; dl; dl = dl->next)
    if (!strcasecmp(dl->name, name))
      return 0;

  datalink_Rename(ndl, name);
  return 1;
}