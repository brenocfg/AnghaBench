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
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  add_kadm_port (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
add_standard_ports (krb5_context contextp)
{
    add_kadm_port(contextp, "kerberos-adm", 749);
}