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
struct pa_info_data {scalar_t__ s2kparams; int /*<<< orphan*/  salt; } ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_free_data (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  krb5_free_salt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_paid(krb5_context context, struct pa_info_data *ppaid)
{
    krb5_free_salt(context, ppaid->salt);
    if (ppaid->s2kparams)
	krb5_free_data(context, ppaid->s2kparams);
}