#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t len; TYPE_1__* val; } ;
struct TYPE_5__ {unsigned int padata_type; } ;
typedef  TYPE_1__ PA_DATA ;
typedef  TYPE_2__ METHOD_DATA ;

/* Variables and functions */

__attribute__((used)) static PA_DATA *
find_pa_data(const METHOD_DATA *md, unsigned type)
{
    size_t i;
    if (md == NULL)
	return NULL;
    for (i = 0; i < md->len; i++)
	if (md->val[i].padata_type == type)
	    return &md->val[i];
    return NULL;
}