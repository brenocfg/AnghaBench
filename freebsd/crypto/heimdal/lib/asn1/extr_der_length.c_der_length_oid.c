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
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 size_t len_oid (int /*<<< orphan*/  const*) ; 

size_t
der_length_oid (const heim_oid *k)
{
    return len_oid (k);
}