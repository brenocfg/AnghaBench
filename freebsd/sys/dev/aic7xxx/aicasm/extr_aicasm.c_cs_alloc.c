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
typedef  int /*<<< orphan*/  critical_section_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_tailq ; 
 int /*<<< orphan*/  links ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop (char*,int /*<<< orphan*/ ) ; 

critical_section_t *
cs_alloc(void)
{
	critical_section_t *new_cs;

	new_cs= (critical_section_t *)malloc(sizeof(critical_section_t));
	if (new_cs == NULL)
		stop("Unable to malloc critical_section object", EX_SOFTWARE);
	memset(new_cs, 0, sizeof(*new_cs));
	
	TAILQ_INSERT_TAIL(&cs_tailq, new_cs, links);
	return new_cs;
}