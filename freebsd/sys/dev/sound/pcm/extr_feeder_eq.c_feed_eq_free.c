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
struct pcm_feeder {struct feed_eq_info* data; } ;
struct feed_eq_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (struct feed_eq_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
feed_eq_free(struct pcm_feeder *f)
{
	struct feed_eq_info *info;

	info = f->data;
	if (info != NULL)
		free(info, M_DEVBUF);

	f->data = NULL;

	return (0);
}