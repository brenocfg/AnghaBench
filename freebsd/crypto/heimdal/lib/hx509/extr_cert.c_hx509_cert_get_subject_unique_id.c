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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  TYPE_3__* hx509_cert ;
typedef  int /*<<< orphan*/  heim_bit_string ;
struct TYPE_7__ {TYPE_2__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  subjectUniqueID; } ;
struct TYPE_6__ {TYPE_1__ tbsCertificate; } ;

/* Variables and functions */
 int get_x_unique_id (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
hx509_cert_get_subject_unique_id(hx509_context context, hx509_cert p, heim_bit_string *subject)
{
    return get_x_unique_id(context, "subject", p->data->tbsCertificate.subjectUniqueID, subject);
}