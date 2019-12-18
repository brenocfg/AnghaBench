#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snmp_context {TYPE_1__* scratch; } ;
struct TYPE_2__ {int /*<<< orphan*/  int1; int /*<<< orphan*/ * ptr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bridge_default_name_save(struct snmp_context *ctx, const char *bridge_default)
{
	if ((ctx->scratch->int1 = strlen(bridge_default)) >= IFNAMSIZ)
		return (-1);

	if ((ctx->scratch->ptr1 = malloc(IFNAMSIZ)) == NULL)
		return (-1);

	strncpy(ctx->scratch->ptr1, bridge_default, ctx->scratch->int1);
	return (0);
}