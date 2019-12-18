#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_cursor ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_2__* hx509_certs ;
struct TYPE_6__ {int /*<<< orphan*/  ops_data; TYPE_1__* ops; } ;
struct TYPE_5__ {int (* iter_start ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HX509_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
hx509_certs_start_seq(hx509_context context,
		      hx509_certs certs,
		      hx509_cursor *cursor)
{
    int ret;

    if (certs->ops->iter_start == NULL) {
	hx509_set_error_string(context, 0, HX509_UNSUPPORTED_OPERATION,
			       "Keyset type %s doesn't support iteration",
			       certs->ops->name);
	return HX509_UNSUPPORTED_OPERATION;
    }

    ret = (*certs->ops->iter_start)(context, certs, certs->ops_data, cursor);
    if (ret)
	return ret;

    return 0;
}