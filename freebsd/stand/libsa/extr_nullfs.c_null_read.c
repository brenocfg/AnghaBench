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
struct open_file {int dummy; } ;

/* Variables and functions */
 int EIO ; 

int	null_read (struct open_file *f, void *buf, size_t size, size_t *resid)
{
	return EIO;
}