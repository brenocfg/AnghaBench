#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* data; size_t size; } ;
struct TYPE_6__ {TYPE_1__ raw; } ;
struct TYPE_7__ {int raw; TYPE_2__ data; } ;
typedef  TYPE_3__ git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 

int git_blob__parse_raw(void *_blob, const char *data, size_t size)
{
	git_blob *blob = (git_blob *) _blob;
	assert(blob);
	blob->raw = 1;
	blob->data.raw.data = data;
	blob->data.raw.size = size;
	return 0;
}