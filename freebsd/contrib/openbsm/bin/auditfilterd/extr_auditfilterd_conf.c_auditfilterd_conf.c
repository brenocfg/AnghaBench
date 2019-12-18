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
struct auditfilter_module_list {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (struct auditfilter_module_list*) ; 
 int /*<<< orphan*/  auditfilterd_conf_apply (struct auditfilter_module_list*) ; 
 scalar_t__ auditfilterd_conf_read (char const*,int /*<<< orphan*/ *,struct auditfilter_module_list*) ; 

int
auditfilterd_conf(const char *filename, FILE *fp)
{
	struct auditfilter_module_list list;

	TAILQ_INIT(&list);
	if (auditfilterd_conf_read(filename, fp, &list) < 0)
		return (-1);

	auditfilterd_conf_apply(&list);

	return (0);
}