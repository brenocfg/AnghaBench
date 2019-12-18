#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int krb5_error_code ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GSMERR_ERROR ; 
 int /*<<< orphan*/  GSMERR_OK ; 

__attribute__((used)) static int32_t
convert_krb5_to_gsm(krb5_error_code ret)
{
    switch(ret) {
    case 0:
	return GSMERR_OK;
    default:
	return GSMERR_ERROR;
    }
}