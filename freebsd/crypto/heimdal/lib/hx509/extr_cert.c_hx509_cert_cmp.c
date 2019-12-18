#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_cert ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int _hx509_Certificate_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
hx509_cert_cmp(hx509_cert p, hx509_cert q)
{
    return _hx509_Certificate_cmp(p->data, q->data);
}