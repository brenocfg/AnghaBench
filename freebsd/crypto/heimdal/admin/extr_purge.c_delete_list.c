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

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/  free (struct e*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
delete_list (struct e *head)
{
    while (head != NULL) {
	struct e *next = head->next;
	krb5_free_principal (context, head->principal);
	free (head);
	head = next;
    }
}