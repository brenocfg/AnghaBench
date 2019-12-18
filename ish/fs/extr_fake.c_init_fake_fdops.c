#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  readdir; } ;

/* Variables and functions */
 TYPE_1__ fakefs_fdops ; 
 int /*<<< orphan*/  fakefs_readdir ; 
 TYPE_1__ realfs_fdops ; 

__attribute__((used)) static void __attribute__((constructor)) init_fake_fdops() {
    fakefs_fdops = realfs_fdops;
    fakefs_fdops.readdir = fakefs_readdir;
}