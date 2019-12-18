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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/ * hx509_ca_tbs ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * calloc (int,int) ; 

int
hx509_ca_tbs_init(hx509_context context, hx509_ca_tbs *tbs)
{
    *tbs = calloc(1, sizeof(**tbs));
    if (*tbs == NULL)
	return ENOMEM;

    return 0;
}