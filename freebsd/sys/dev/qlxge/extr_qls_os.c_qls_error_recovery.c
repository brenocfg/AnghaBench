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
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qls_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qls_error_recovery(void *context, int pending)
{
        qla_host_t *ha = context;

	qls_init(ha);

	return;
}