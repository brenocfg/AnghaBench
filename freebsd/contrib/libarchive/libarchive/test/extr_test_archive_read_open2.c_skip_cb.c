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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t
skip_cb(struct archive *a, void *client, int64_t request)
{
	(void)a; /* UNUSED */
	(void)client; /* UNUSED */
	(void)request; /* UNUSED */
	return (int64_t)0;
}