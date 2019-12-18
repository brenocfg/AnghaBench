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
typedef  int /*<<< orphan*/  hx509_private_key ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_2__* hx509_certs ;
struct TYPE_6__ {int /*<<< orphan*/  ops_data; TYPE_1__* ops; } ;
struct TYPE_5__ {int (* addkey ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
_hx509_certs_keys_add(hx509_context context,
		      hx509_certs certs,
		      hx509_private_key key)
{
    if (certs->ops->addkey == NULL) {
	hx509_set_error_string(context, 0, EINVAL,
			       "keystore if type %s doesn't support "
			       "key add operation",
			       certs->ops->name);
	return EINVAL;
    }
    return (*certs->ops->addkey)(context, certs, certs->ops_data, key);
}