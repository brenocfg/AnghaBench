#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fpreg {int dummy; } ;
typedef  int /*<<< orphan*/  elfcore_fpregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct fpreg*,int) ; 

__attribute__((used)) static void
elf_convert_fpregset(elfcore_fpregset_t *rd, struct fpreg *rs)
{
#ifdef __amd64__
	/* XXX this is wrong... */
	memcpy(rd, rs, sizeof(*rd));
#elif defined(__aarch64__)
	/* ARM64TODO */
#elif defined(__powerpc64__)
	memcpy(rd, rs, sizeof(*rd));
#else
#error Unsupported architecture
#endif
}