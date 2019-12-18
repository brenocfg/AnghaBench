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
 int /*<<< orphan*/  t_cmsgcred_client ; 
 int /*<<< orphan*/  t_cmsgcred_sockcred_server ; 
 int t_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
t_cmsgcred_sockcred(void)
{
	return (t_generic(t_cmsgcred_client, t_cmsgcred_sockcred_server));
}