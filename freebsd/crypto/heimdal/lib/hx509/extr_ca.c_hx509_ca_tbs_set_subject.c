#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_1__* hx509_ca_tbs ;
struct TYPE_3__ {scalar_t__ subject; } ;

/* Variables and functions */
 int hx509_name_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  hx509_name_free (scalar_t__*) ; 

int
hx509_ca_tbs_set_subject(hx509_context context,
			 hx509_ca_tbs tbs,
			 hx509_name subject)
{
    if (tbs->subject)
	hx509_name_free(&tbs->subject);
    return hx509_name_copy(context, subject, &tbs->subject);
}