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
struct xs_transaction {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_XENSTORE ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  XS_TRANSACTION_START ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xs_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,void**) ; 

int
xs_transaction_start(struct xs_transaction *t)
{
	char *id_str;
	int error;

	error = xs_single(XST_NIL, XS_TRANSACTION_START, "", NULL,
	    (void **)&id_str);
	if (error == 0) {
		t->id = strtoul(id_str, NULL, 0);
		free(id_str, M_XENSTORE);
	}
	return (error);
}