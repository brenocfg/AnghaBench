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
typedef  int /*<<< orphan*/  linker_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  fbt_provide_module (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fbt_linker_file_cb(linker_file_t lf, void *arg)
{

	fbt_provide_module(arg, lf);

	return (0);
}