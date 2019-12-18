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
typedef  union ipdu_u {int dummy; } ipdu_u ;
struct TYPE_3__ {scalar_t__ ds_len; scalar_t__ ds_size; scalar_t__ ahs_size; int /*<<< orphan*/ * ds_addr; int /*<<< orphan*/ * ahs_addr; int /*<<< orphan*/  ipdu; } ;
typedef  TYPE_1__ pdu_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
freePDU(pdu_t *pp)
{
     if(pp->ahs_size)
	  free(pp->ahs_addr);
     if(pp->ds_size)
	  free(pp->ds_addr);
     bzero(&pp->ipdu, sizeof(union ipdu_u));
     pp->ahs_addr = NULL;
     pp->ds_addr = NULL;
     pp->ahs_size = 0;
     pp->ds_size = pp->ds_len = 0;
}