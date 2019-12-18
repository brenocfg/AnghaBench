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
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */

__attribute__((used)) static ssize_t
read_cb(struct archive *a, void *client, const void **buff)
{
	(void)a; /* UNUSED */
	(void)client; /* UNUSED */
	(void)buff; /* UNUSED */
	return (ssize_t)0;
}