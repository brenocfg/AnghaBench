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
typedef  int /*<<< orphan*/  krb5_flags ;

/* Variables and functions */
 int /*<<< orphan*/  kdb_attrs ; 
 int /*<<< orphan*/  unparse_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

void
attributes2str(krb5_flags attributes, char *str, size_t len)
{
    unparse_flags (attributes, kdb_attrs, str, len);
}