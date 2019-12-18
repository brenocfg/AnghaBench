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
struct TYPE_2__ {struct data_ready* dready; } ;
struct rar5 {TYPE_1__ cstate; } ;
struct data_ready {void* buf; size_t size; scalar_t__ used; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_RETRY ; 
 int rar5_countof (struct data_ready*) ; 

__attribute__((used)) static int use_data(struct rar5* rar, const void** buf, size_t* size,
    int64_t* offset)
{
	int i;

	for(i = 0; i < rar5_countof(rar->cstate.dready); i++) {
		struct data_ready *d = &rar->cstate.dready[i];

		if(d->used) {
			if(buf)    *buf = d->buf;
			if(size)   *size = d->size;
			if(offset) *offset = d->offset;

			d->used = 0;
			return ARCHIVE_OK;
		}
	}

	return ARCHIVE_RETRY;
}