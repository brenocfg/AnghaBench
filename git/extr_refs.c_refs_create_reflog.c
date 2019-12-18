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
struct strbuf {int dummy; } ;
struct ref_store {TYPE_1__* be; } ;
struct TYPE_2__ {int (* create_reflog ) (struct ref_store*,char const*,int,struct strbuf*) ;} ;

/* Variables and functions */
 int stub1 (struct ref_store*,char const*,int,struct strbuf*) ; 

int refs_create_reflog(struct ref_store *refs, const char *refname,
		       int force_create, struct strbuf *err)
{
	return refs->be->create_reflog(refs, refname, force_create, err);
}