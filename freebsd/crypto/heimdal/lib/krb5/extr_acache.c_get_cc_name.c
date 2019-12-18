#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * cache_name; TYPE_6__* ccache; } ;
typedef  TYPE_3__ krb5_acc ;
typedef  TYPE_4__* cc_string_t ;
typedef  scalar_t__ cc_int32 ;
struct TYPE_13__ {TYPE_1__* func; } ;
struct TYPE_12__ {TYPE_2__* func; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* release ) (TYPE_4__*) ;} ;
struct TYPE_9__ {scalar_t__ (* get_name ) (TYPE_6__*,TYPE_4__**) ;} ;

/* Variables and functions */
 scalar_t__ ccErrNoMem ; 
 scalar_t__ ccNoError ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_6__*,TYPE_4__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 

__attribute__((used)) static cc_int32
get_cc_name(krb5_acc *a)
{
    cc_string_t name;
    cc_int32 error;

    error = (*a->ccache->func->get_name)(a->ccache, &name);
    if (error)
	return error;

    a->cache_name = strdup(name->data);
    (*name->func->release)(name);
    if (a->cache_name == NULL)
	return ccErrNoMem;
    return ccNoError;
}