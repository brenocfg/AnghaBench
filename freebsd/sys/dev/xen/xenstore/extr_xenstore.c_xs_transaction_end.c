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
struct xs_transaction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XS_TRANSACTION_END ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int xs_single (struct xs_transaction,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xs_transaction_end(struct xs_transaction t, int abort)
{
	char abortstr[2];

	if (abort)
		strcpy(abortstr, "F");
	else
		strcpy(abortstr, "T");

	return (xs_single(t, XS_TRANSACTION_END, abortstr, NULL, NULL));
}