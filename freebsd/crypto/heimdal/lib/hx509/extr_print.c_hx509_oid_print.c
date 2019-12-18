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
typedef  int /*<<< orphan*/  hx509_vprint_func ;
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_oid_sprint (int /*<<< orphan*/  const*,char**) ; 
 int /*<<< orphan*/  print_func (int /*<<< orphan*/ ,void*,char*,char*) ; 

void
hx509_oid_print(const heim_oid *oid, hx509_vprint_func func, void *ctx)
{
    char *str;
    hx509_oid_sprint(oid, &str);
    print_func(func, ctx, "%s", str);
    free(str);
}