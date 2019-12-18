#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ expr; struct TYPE_8__* friendlyname; struct TYPE_8__* eku; struct TYPE_8__* issuer_name; struct TYPE_8__* serial; } ;
typedef  TYPE_1__ hx509_query ;
typedef  int /*<<< orphan*/  hx509_context ;

/* Variables and functions */
 int /*<<< orphan*/  _hx509_expr_free (scalar_t__) ; 
 int /*<<< orphan*/  der_free_heim_integer (TYPE_1__*) ; 
 int /*<<< orphan*/  der_free_oid (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_Name (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
hx509_query_free(hx509_context context, hx509_query *q)
{
    if (q == NULL)
	return;

    if (q->serial) {
	der_free_heim_integer(q->serial);
	free(q->serial);
    }
    if (q->issuer_name) {
	free_Name(q->issuer_name);
	free(q->issuer_name);
    }
    if (q->eku) {
	der_free_oid(q->eku);
	free(q->eku);
    }
    if (q->friendlyname)
	free(q->friendlyname);
    if (q->expr)
	_hx509_expr_free(q->expr);

    memset(q, 0, sizeof(*q));
    free(q);
}