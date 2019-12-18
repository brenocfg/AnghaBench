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
struct open_file {int /*<<< orphan*/  f_fsdata; } ;

/* Variables and functions */
 int CALLBACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,size_t*) ; 
 int /*<<< orphan*/  read ; 

__attribute__((used)) static int
host_read(struct open_file *f, void *start, size_t size, size_t *resid)
{

	return (CALLBACK(read, f->f_fsdata, start, size, resid));
}