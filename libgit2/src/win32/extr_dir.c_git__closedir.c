#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ h; } ;
typedef  TYPE_1__ git__DIR ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

int git__closedir(git__DIR *d)
{
	if (!d)
		return 0;

	if (d->h != INVALID_HANDLE_VALUE) {
		FindClose(d->h);
		d->h = INVALID_HANDLE_VALUE;
	}

	git__free(d);
	return 0;
}