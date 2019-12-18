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
typedef  void* time_t ;
struct e {int max_vno; struct e* next; void* timestamp; int /*<<< orphan*/  principal; } ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 struct e* get_entry (int /*<<< orphan*/ ,struct e*) ; 
 scalar_t__ krb5_copy_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 struct e* malloc (int) ; 

__attribute__((used)) static void
add_entry (krb5_principal princ, int vno, time_t timestamp, struct e **head)
{
    krb5_error_code ret;
    struct e *e;

    e = get_entry (princ, *head);
    if (e != NULL) {
	if(e->max_vno < vno) {
	    e->max_vno = vno;
	    e->timestamp = timestamp;
	}
	return;
    }
    e = malloc (sizeof (*e));
    if (e == NULL)
	krb5_errx (context, 1, "malloc: out of memory");
    ret = krb5_copy_principal (context, princ, &e->principal);
    if (ret)
	krb5_err (context, 1, ret, "krb5_copy_principal");
    e->max_vno = vno;
    e->timestamp = timestamp;
    e->next    = *head;
    *head      = e;
}