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
struct diff_queue_struct {int nr; TYPE_2__** queue; } ;
struct diff_options {int dummy; } ;
struct TYPE_4__ {TYPE_1__* one; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addch (void*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_diff_to_buf(struct diff_queue_struct *q,
			    struct diff_options *options,
			    void *data)
{
	int i;

	for (i = 0; i < q->nr; i++) {
		strbuf_addstr(data, q->queue[i]->one->path);

		/* NUL-terminate: will be fed to update-index -z */
		strbuf_addch(data, '\0');
	}
}