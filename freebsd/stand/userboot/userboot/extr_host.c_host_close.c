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
struct open_file {void* f_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLBACK (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  close ; 

__attribute__((used)) static int
host_close(struct open_file *f)
{

        CALLBACK(close, f->f_fsdata);
	f->f_fsdata = (void *)0;

	return (0);
}