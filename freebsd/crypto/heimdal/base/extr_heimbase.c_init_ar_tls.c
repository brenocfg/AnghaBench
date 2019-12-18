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

/* Variables and functions */
 int /*<<< orphan*/  HEIMDAL_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ar_created ; 
 int /*<<< orphan*/  ar_key ; 
 int /*<<< orphan*/  ar_tls_delete ; 

__attribute__((used)) static void
init_ar_tls(void *ptr)
{
    int ret;
    HEIMDAL_key_create(&ar_key, ar_tls_delete, ret);
    if (ret == 0)
	ar_created = 1;
}