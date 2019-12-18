#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int modified; } ;
struct TYPE_6__ {int /*<<< orphan*/  version; TYPE_1__ enc; } ;
struct TYPE_7__ {TYPE_2__ req_info; } ;
typedef  TYPE_3__ X509_REQ ;

/* Variables and functions */
 int ASN1_INTEGER_set (int /*<<< orphan*/ ,long) ; 

int X509_REQ_set_version(X509_REQ *x, long version)
{
    if (x == NULL)
        return 0;
    x->req_info.enc.modified = 1;
    return ASN1_INTEGER_set(x->req_info.version, version);
}