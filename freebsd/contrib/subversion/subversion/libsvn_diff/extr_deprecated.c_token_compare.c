#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct fns_wrapper_baton {int /*<<< orphan*/  old_baton; TYPE_1__* vtable; } ;
struct TYPE_2__ {int /*<<< orphan*/ * (* token_compare ) (int /*<<< orphan*/ ,void*,void*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,void*,void*,int*) ; 

__attribute__((used)) static svn_error_t *
token_compare(void *baton,
              void *ltoken,
              void *rtoken,
              int *compare)
{
  struct fns_wrapper_baton *fwb = baton;
  return fwb->vtable->token_compare(fwb->old_baton, ltoken, rtoken, compare);
}