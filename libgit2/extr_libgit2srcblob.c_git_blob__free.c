#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  odb; } ;
struct TYPE_5__ {TYPE_1__ data; int /*<<< orphan*/  raw; } ;
typedef  TYPE_2__ git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ ) ; 

void git_blob__free(void *_blob)
{
	git_blob *blob = (git_blob *) _blob;
	if (!blob->raw)
		git_odb_object_free(blob->data.odb);
	git__free(blob);
}