#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* padata; } ;
struct TYPE_7__ {unsigned int padata_type; } ;
struct TYPE_6__ {size_t len; TYPE_2__ const* val; } ;
typedef  TYPE_2__ PA_DATA ;
typedef  TYPE_3__ KDC_REQ ;

/* Variables and functions */

const PA_DATA*
_kdc_find_padata(const KDC_REQ *req, int *start, int type)
{
    if (req->padata == NULL)
	return NULL;

    while((size_t)*start < req->padata->len){
	(*start)++;
	if(req->padata->val[*start - 1].padata_type == (unsigned)type)
	    return &req->padata->val[*start - 1];
    }
    return NULL;
}