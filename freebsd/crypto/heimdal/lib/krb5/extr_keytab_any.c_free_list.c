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
struct any_data {scalar_t__ kt; struct any_data* name; struct any_data* next; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct any_data*) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
free_list (krb5_context context, struct any_data *a)
{
    struct any_data *next;

    for (; a != NULL; a = next) {
	next = a->next;
	free (a->name);
	if(a->kt)
	    krb5_kt_close(context, a->kt);
	free (a);
    }
}