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
struct TYPE_4__ {int fa_flags; } ;
typedef  TYPE_1__ fileargs_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cap_init () ; 
 int /*<<< orphan*/  fileargs_free (TYPE_1__*) ; 

__attribute__((used)) static inline cap_channel_t *
fileargs_unwrap(fileargs_t *fa, int *fdflags)
{

	if (fdflags != NULL) {
		*fdflags = fa->fa_flags;
	}
	fileargs_free(fa);
	return (cap_init());
}