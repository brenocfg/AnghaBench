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
struct _region {int dummy; } ;
struct _citrus_lookup {int (* cl_next ) (struct _citrus_lookup*,struct _region*,struct _region*) ;} ;

/* Variables and functions */
 int stub1 (struct _citrus_lookup*,struct _region*,struct _region*) ; 

int
_citrus_lookup_seq_next(struct _citrus_lookup *cl,
    struct _region *key, struct _region *data)
{

	return ((*cl->cl_next)(cl, key, data));
}