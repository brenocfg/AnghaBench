#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* protocol; struct TYPE_5__* method; struct TYPE_5__* data; } ;
struct TYPE_4__ {TYPE_3__* metrics; int /*<<< orphan*/ * sub_list; } ;
typedef  TYPE_1__ GHolderItem ;

/* Variables and functions */
 int /*<<< orphan*/  delete_sub_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void
free_holder_data (GHolderItem item)
{
  if (item.sub_list != NULL)
    delete_sub_list (item.sub_list);
  if (item.metrics->data != NULL)
    free (item.metrics->data);
  if (item.metrics->method != NULL)
    free (item.metrics->method);
  if (item.metrics->protocol != NULL)
    free (item.metrics->protocol);
  if (item.metrics != NULL)
    free (item.metrics);
}