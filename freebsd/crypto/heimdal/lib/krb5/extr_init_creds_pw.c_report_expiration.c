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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  (* krb5_prompter_fct ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 scalar_t__ asprintf (char**,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
report_expiration (krb5_context context,
		   krb5_prompter_fct prompter,
		   krb5_data *data,
		   const char *str,
		   time_t now)
{
    char *p = NULL;

    if (asprintf(&p, "%s%s", str, ctime(&now)) < 0 || p == NULL)
	return;
    (*prompter)(context, data, NULL, p, 0, NULL);
    free(p);
}