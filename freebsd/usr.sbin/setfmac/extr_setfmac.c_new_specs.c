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
struct label_specs {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct label_specs* malloc (int) ; 

struct label_specs *
new_specs(void)
{
	struct label_specs *specs;

	specs = malloc(sizeof(*specs));
	if (specs == NULL)
		err(1, "malloc");
	STAILQ_INIT(&specs->head);
	return (specs);
}