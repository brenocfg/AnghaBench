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
struct datalink {struct datalink* next; } ;
struct bundle {struct datalink* links; } ;

/* Variables and functions */
 int /*<<< orphan*/  bundle_LinksRemoved (struct bundle*) ; 

__attribute__((used)) static struct datalink *
bundle_DatalinkLinkout(struct bundle *bundle, struct datalink *dl)
{
  struct datalink **dlp;

  for (dlp = &bundle->links; *dlp; dlp = &(*dlp)->next)
    if (*dlp == dl) {
      *dlp = dl->next;
      dl->next = NULL;
      bundle_LinksRemoved(bundle);
      return dl;
    }

  return NULL;
}