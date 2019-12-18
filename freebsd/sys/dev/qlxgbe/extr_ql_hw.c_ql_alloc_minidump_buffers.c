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
 int ql_alloc_minidump_buffer (int /*<<< orphan*/ *) ; 
 int ql_alloc_minidump_template_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_free_minidump_template_buffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ql_alloc_minidump_buffers(qla_host_t *ha)
{
	int ret;

	ret = ql_alloc_minidump_template_buffer(ha);

	if (ret)
		return (ret);

	ret = ql_alloc_minidump_buffer(ha);

	if (ret)
		ql_free_minidump_template_buffer(ha);

	return (ret);
}