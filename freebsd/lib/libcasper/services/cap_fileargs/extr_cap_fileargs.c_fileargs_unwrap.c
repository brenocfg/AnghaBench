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
struct TYPE_4__ {scalar_t__ fa_magic; int fa_fdflags; int /*<<< orphan*/  fa_cache; int /*<<< orphan*/ * fa_chann; } ;
typedef  TYPE_1__ fileargs_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 scalar_t__ FILEARGS_MAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  explicit_bzero (scalar_t__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ ) ; 

cap_channel_t *
fileargs_unwrap(fileargs_t *fa, int *flags)
{
	cap_channel_t *chan;

	if (fa == NULL)
		return (NULL);

	assert(fa->fa_magic == FILEARGS_MAGIC);

	chan = fa->fa_chann;
	if (flags != NULL) {
		*flags = fa->fa_fdflags;
	}

	nvlist_destroy(fa->fa_cache);
	explicit_bzero(&fa->fa_magic, sizeof(fa->fa_magic));
	free(fa);

	return (chan);
}