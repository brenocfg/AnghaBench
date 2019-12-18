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
struct TYPE_3__ {int /*<<< orphan*/  const* certId; } ;
typedef  TYPE_1__ OCSP_SINGLERESP ;
typedef  int /*<<< orphan*/  OCSP_CERTID ;

/* Variables and functions */

const OCSP_CERTID *OCSP_SINGLERESP_get0_id(const OCSP_SINGLERESP *single)
{
    return single->certId;
}