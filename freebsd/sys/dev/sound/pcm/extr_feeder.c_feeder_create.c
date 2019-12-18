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
struct pcm_feederdesc {scalar_t__ idx; scalar_t__ flags; scalar_t__ out; scalar_t__ in; int /*<<< orphan*/  type; } ;
struct pcm_feeder {struct pcm_feederdesc* desc; struct pcm_feederdesc desc_static; struct feeder_class* class; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * source; int /*<<< orphan*/  data; } ;
struct feeder_class {char* name; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  kobj_class_t ;

/* Variables and functions */
 int FEEDER_INIT (struct pcm_feeder*) ; 
 int /*<<< orphan*/  FEEDER_ROOT ; 
 int /*<<< orphan*/  M_FEEDER ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  feeder_destroy (struct pcm_feeder*) ; 
 scalar_t__ kobj_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,struct pcm_feeder*,char*,int) ; 

__attribute__((used)) static struct pcm_feeder *
feeder_create(struct feeder_class *fc, struct pcm_feederdesc *desc)
{
	struct pcm_feeder *f;
	int err;

	f = (struct pcm_feeder *)kobj_create((kobj_class_t)fc, M_FEEDER, M_NOWAIT | M_ZERO);
	if (f == NULL)
		return NULL;

	f->data = fc->data;
	f->source = NULL;
	f->parent = NULL;
	f->class = fc;
	f->desc = &(f->desc_static);

	if (desc) {
		*(f->desc) = *desc;
	} else {
		f->desc->type = FEEDER_ROOT;
		f->desc->in = 0;
		f->desc->out = 0;
		f->desc->flags = 0;
		f->desc->idx = 0;
	}

	err = FEEDER_INIT(f);
	if (err) {
		printf("feeder_init(%p) on %s returned %d\n", f, fc->name, err);
		feeder_destroy(f);

		return NULL;
	}

	return f;
}