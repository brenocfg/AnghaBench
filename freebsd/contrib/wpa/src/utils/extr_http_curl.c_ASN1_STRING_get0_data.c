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
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 unsigned char const* ASN1_STRING_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const unsigned char * ASN1_STRING_get0_data(const ASN1_STRING *x)
{
	return ASN1_STRING_data((ASN1_STRING *) x);
}