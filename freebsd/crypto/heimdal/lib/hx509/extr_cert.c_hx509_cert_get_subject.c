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
typedef  int /*<<< orphan*/  hx509_name ;
typedef  TYPE_3__* hx509_cert ;
struct TYPE_7__ {TYPE_2__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  subject; } ;
struct TYPE_6__ {TYPE_1__ tbsCertificate; } ;

/* Variables and functions */
 int _hx509_name_from_Name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
hx509_cert_get_subject(hx509_cert p, hx509_name *name)
{
    return _hx509_name_from_Name(&p->data->tbsCertificate.subject, name);
}