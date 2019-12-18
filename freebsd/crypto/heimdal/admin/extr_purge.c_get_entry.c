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
struct e {int /*<<< orphan*/  principal; struct e* next; } ;
typedef  int /*<<< orphan*/  krb5_principal ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 scalar_t__ krb5_principal_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct e *
get_entry (krb5_principal princ, struct e *head)
{
    struct e *e;

    for (e = head; e != NULL; e = e->next)
	if (krb5_principal_compare (context, princ, e->principal))
	    return e;
    return NULL;
}