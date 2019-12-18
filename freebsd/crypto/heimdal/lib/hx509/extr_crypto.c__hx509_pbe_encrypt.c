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
typedef  int /*<<< orphan*/  hx509_lock ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_octet_string ;
typedef  int /*<<< orphan*/  AlgorithmIdentifier ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hx509_clear_error_string (int /*<<< orphan*/ ) ; 

int
_hx509_pbe_encrypt(hx509_context context,
		   hx509_lock lock,
		   const AlgorithmIdentifier *ai,
		   const heim_octet_string *content,
		   heim_octet_string *econtent)
{
    hx509_clear_error_string(context);
    return EINVAL;
}