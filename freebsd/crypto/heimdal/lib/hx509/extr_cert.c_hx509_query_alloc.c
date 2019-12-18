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
typedef  int /*<<< orphan*/  hx509_query ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * calloc (int,int) ; 

int
hx509_query_alloc(hx509_context context, hx509_query **q)
{
    *q = calloc(1, sizeof(**q));
    if (*q == NULL)
	return ENOMEM;
    return 0;
}