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
struct datalink {int dummy; } ;
struct bundle {int dummy; } ;

/* Variables and functions */
 struct datalink* bundle_DatalinkLinkout (struct bundle*,struct datalink*) ; 
 int /*<<< orphan*/  datalink_Destroy (struct datalink*) ; 

void
bundle_DatalinkRemove(struct bundle *bundle, struct datalink *dl)
{
  dl = bundle_DatalinkLinkout(bundle, dl);
  if (dl)
    datalink_Destroy(dl);
}