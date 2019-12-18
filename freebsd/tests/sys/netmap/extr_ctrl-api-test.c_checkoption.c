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
struct nmreq_option {scalar_t__ nro_next; void* nro_reqtype; void* nro_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,void*,void*) ; 

__attribute__((used)) static int
checkoption(struct nmreq_option *opt, struct nmreq_option *exp)
{
	if (opt->nro_next != exp->nro_next) {
		printf("nro_next %p expected %p\n",
		       (void *)(uintptr_t)opt->nro_next,
		       (void *)(uintptr_t)exp->nro_next);
		return -1;
	}
	if (opt->nro_reqtype != exp->nro_reqtype) {
		printf("nro_reqtype %u expected %u\n", opt->nro_reqtype,
		       exp->nro_reqtype);
		return -1;
	}
	if (opt->nro_status != exp->nro_status) {
		printf("nro_status %u expected %u\n", opt->nro_status,
		       exp->nro_status);
		return -1;
	}
	return 0;
}