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
struct TYPE_3__ {int match; int /*<<< orphan*/ * issuer_name; int /*<<< orphan*/ * serial; } ;
typedef  TYPE_1__ hx509_query ;
typedef  int /*<<< orphan*/  heim_integer ;
typedef  int /*<<< orphan*/  Name ;

/* Variables and functions */
 int ENOMEM ; 
 int HX509_QUERY_MATCH_ISSUER_NAME ; 
 int HX509_QUERY_MATCH_SERIALNUMBER ; 
 int copy_Name (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int der_copy_heim_integer (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  der_free_heim_integer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_Name (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 

int
hx509_query_match_issuer_serial(hx509_query *q,
				const Name *issuer,
				const heim_integer *serialNumber)
{
    int ret;
    if (q->serial) {
	der_free_heim_integer(q->serial);
	free(q->serial);
    }
    q->serial = malloc(sizeof(*q->serial));
    if (q->serial == NULL)
	return ENOMEM;
    ret = der_copy_heim_integer(serialNumber, q->serial);
    if (ret) {
	free(q->serial);
	q->serial = NULL;
	return ret;
    }
    if (q->issuer_name) {
	free_Name(q->issuer_name);
	free(q->issuer_name);
    }
    q->issuer_name = malloc(sizeof(*q->issuer_name));
    if (q->issuer_name == NULL)
	return ENOMEM;
    ret = copy_Name(issuer, q->issuer_name);
    if (ret) {
	free(q->issuer_name);
	q->issuer_name = NULL;
	return ret;
    }
    q->match |= HX509_QUERY_MATCH_SERIALNUMBER|HX509_QUERY_MATCH_ISSUER_NAME;
    return 0;
}