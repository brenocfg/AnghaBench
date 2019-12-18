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
struct TYPE_5__ {int /*<<< orphan*/  notBefore; } ;
struct TYPE_6__ {TYPE_1__ validity; } ;
struct TYPE_7__ {TYPE_2__ cert_info; } ;
typedef  TYPE_3__ X509 ;
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int x509_set1_time (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int X509_set1_notBefore(X509 *x, const ASN1_TIME *tm)
{
    if (x == NULL)
        return 0;
    return x509_set1_time(&x->cert_info.validity.notBefore, tm);
}