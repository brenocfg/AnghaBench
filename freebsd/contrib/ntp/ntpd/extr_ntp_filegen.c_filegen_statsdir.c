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
struct filegen_entry {TYPE_1__* filegen; struct filegen_entry* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  type; int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int /*<<< orphan*/  filegen_config (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct filegen_entry* filegen_registry ; 
 int /*<<< orphan*/  statsdir ; 

void
filegen_statsdir(void)
{
	struct filegen_entry *f;

	for (f = filegen_registry; f != NULL; f = f->next)
		filegen_config(f->filegen, statsdir, f->filegen->fname,
			       f->filegen->type, f->filegen->flag);
}