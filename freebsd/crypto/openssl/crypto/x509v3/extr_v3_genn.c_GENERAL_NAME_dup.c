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
typedef  int /*<<< orphan*/  i2d_of_void ;
typedef  int /*<<< orphan*/  d2i_of_void ;
typedef  int /*<<< orphan*/  GENERAL_NAME ;

/* Variables and functions */
 scalar_t__ ASN1_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ d2i_GENERAL_NAME ; 
 scalar_t__ i2d_GENERAL_NAME ; 

GENERAL_NAME *GENERAL_NAME_dup(GENERAL_NAME *a)
{
    return (GENERAL_NAME *)ASN1_dup((i2d_of_void *)i2d_GENERAL_NAME,
                                    (d2i_of_void *)d2i_GENERAL_NAME,
                                    (char *)a);
}