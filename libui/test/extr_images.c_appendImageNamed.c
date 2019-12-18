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
typedef  int /*<<< orphan*/  uiImage ;
struct TYPE_2__ {int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__* files ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiImageAppend (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void appendImageNamed(uiImage *img, const char *name)
{
	int i;

	i = 0;
	for (;;) {
		if (strcmp(name, files[i].name) == 0) {
			uiImageAppend(img, files[i].data, files[i].width, files[i].height, files[i].stride);
			return;
		}
		i++;
	}
}