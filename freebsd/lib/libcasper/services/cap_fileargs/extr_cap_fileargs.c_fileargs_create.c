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
struct TYPE_4__ {int fa_fdflags; int /*<<< orphan*/  fa_magic; int /*<<< orphan*/ * fa_chann; int /*<<< orphan*/ * fa_cache; } ;
typedef  TYPE_1__ fileargs_t ;
typedef  int /*<<< orphan*/  cap_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILEARGS_MAGIC ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static fileargs_t *
fileargs_create(cap_channel_t *chan, int fdflags)
{
	fileargs_t *fa;

	fa = malloc(sizeof(*fa));
	if (fa != NULL) {
		fa->fa_cache = NULL;
		fa->fa_chann = chan;
		fa->fa_fdflags = fdflags;
		fa->fa_magic = FILEARGS_MAGIC;
	}

	return (fa);
}