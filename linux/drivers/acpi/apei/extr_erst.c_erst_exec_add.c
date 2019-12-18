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
struct apei_exec_context {scalar_t__ var2; int /*<<< orphan*/  var1; } ;
struct acpi_whea_header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int erst_exec_add(struct apei_exec_context *ctx,
			 struct acpi_whea_header *entry)
{
	ctx->var1 += ctx->var2;
	return 0;
}