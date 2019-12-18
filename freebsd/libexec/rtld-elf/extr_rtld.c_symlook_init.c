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
struct TYPE_4__ {char const* name; int /*<<< orphan*/  hash_gnu; int /*<<< orphan*/  hash; } ;
typedef  TYPE_1__ SymLook ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  elf_hash (char const*) ; 
 int /*<<< orphan*/  gnu_hash (char const*) ; 

void
symlook_init(SymLook *dst, const char *name)
{

	bzero(dst, sizeof(*dst));
	dst->name = name;
	dst->hash = elf_hash(name);
	dst->hash_gnu = gnu_hash(name);
}