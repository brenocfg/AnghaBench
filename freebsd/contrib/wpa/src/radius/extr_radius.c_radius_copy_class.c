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
struct radius_class_data {size_t count; TYPE_1__* attr; } ;
struct radius_attr_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 TYPE_1__* os_calloc (size_t,int) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int radius_copy_class(struct radius_class_data *dst,
		      const struct radius_class_data *src)
{
	size_t i;

	if (src->attr == NULL)
		return 0;

	dst->attr = os_calloc(src->count, sizeof(struct radius_attr_data));
	if (dst->attr == NULL)
		return -1;

	dst->count = 0;

	for (i = 0; i < src->count; i++) {
		dst->attr[i].data = os_memdup(src->attr[i].data,
					      src->attr[i].len);
		if (dst->attr[i].data == NULL)
			break;
		dst->count++;
		dst->attr[i].len = src->attr[i].len;
	}

	return 0;
}