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

/* Variables and functions */
 int /*<<< orphan*/  unlinkat (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
symlinks_remove(int savedirfd)
{

	(void)unlinkat(savedirfd, "info.last", 0);
	(void)unlinkat(savedirfd, "key.last", 0);
	(void)unlinkat(savedirfd, "vmcore.last", 0);
	(void)unlinkat(savedirfd, "vmcore.last.gz", 0);
	(void)unlinkat(savedirfd, "vmcore.last.zst", 0);
	(void)unlinkat(savedirfd, "vmcore_encrypted.last", 0);
	(void)unlinkat(savedirfd, "vmcore_encrypted.last.gz", 0);
	(void)unlinkat(savedirfd, "textdump.tar.last", 0);
	(void)unlinkat(savedirfd, "textdump.tar.last.gz", 0);
}