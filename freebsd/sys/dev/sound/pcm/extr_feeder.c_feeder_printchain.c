#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcm_feeder {struct pcm_feeder* source; TYPE_2__* desc; TYPE_1__* class; } ;
struct TYPE_4__ {int idx; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
feeder_printchain(struct pcm_feeder *head)
{
	struct pcm_feeder *f;

	printf("feeder chain (head @%p)\n", head);
	f = head;
	while (f != NULL) {
		printf("%s/%d @ %p\n", f->class->name, f->desc->idx, f);
		f = f->source;
	}
	printf("[end]\n\n");
}