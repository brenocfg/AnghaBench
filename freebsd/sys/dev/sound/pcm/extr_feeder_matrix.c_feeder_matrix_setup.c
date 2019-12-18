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
struct pcmchan_matrix {int dummy; } ;
struct pcm_feeder {int /*<<< orphan*/ * data; TYPE_1__* desc; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FEEDER_MATRIX ; 
 int feed_matrix_setup (int /*<<< orphan*/ *,struct pcmchan_matrix*,struct pcmchan_matrix*) ; 

int
feeder_matrix_setup(struct pcm_feeder *f, struct pcmchan_matrix *m_in,
    struct pcmchan_matrix *m_out)
{

	if (f == NULL || f->desc == NULL || f->desc->type != FEEDER_MATRIX ||
	    f->data == NULL)
		return (EINVAL);

	return (feed_matrix_setup(f->data, m_in, m_out));
}