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
typedef  TYPE_1__* hx509_cert ;
typedef  int /*<<< orphan*/  _hx509_cert_release_func ;
struct TYPE_3__ {void* ctx; int /*<<< orphan*/  release; } ;

/* Variables and functions */

void
_hx509_cert_set_release(hx509_cert cert,
			_hx509_cert_release_func release,
			void *ctx)
{
    cert->release = release;
    cert->ctx = ctx;
}