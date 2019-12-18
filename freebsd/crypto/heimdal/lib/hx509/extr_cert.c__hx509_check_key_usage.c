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
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  hx509_cert ;

/* Variables and functions */
 int /*<<< orphan*/  _hx509_get_cert (int /*<<< orphan*/ ) ; 
 int check_key_usage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

int
_hx509_check_key_usage(hx509_context context, hx509_cert cert,
		       unsigned flags, int req_present)
{
    return check_key_usage(context, _hx509_get_cert(cert), flags, req_present);
}