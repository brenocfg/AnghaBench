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
struct datalink {struct datalink* next; int /*<<< orphan*/  name; } ;
struct bundle {struct datalink* links; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 

struct datalink *
bundle2datalink(struct bundle *bundle, const char *name)
{
  struct datalink *dl;

  if (name != NULL) {
    for (dl = bundle->links; dl; dl = dl->next)
      if (!strcasecmp(dl->name, name))
        return dl;
  } else if (bundle->links && !bundle->links->next)
    return bundle->links;

  return NULL;
}