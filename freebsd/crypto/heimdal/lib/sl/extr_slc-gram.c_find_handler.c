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
struct type_handler {int /*<<< orphan*/ * typename; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct assignment {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ex (struct assignment*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct type_handler* type_handlers ; 

__attribute__((used)) static struct type_handler *find_handler(struct assignment *type)
{
    struct type_handler *th;
    for(th = type_handlers; th->typename != NULL; th++)
	if(strcmp(type->u.value, th->typename) == 0)
	    return th;
    ex(type, "unknown type \"%s\"", type->u.value);
    exit(1);
}