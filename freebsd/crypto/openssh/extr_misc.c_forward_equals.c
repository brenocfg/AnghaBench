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
struct Forward {scalar_t__ listen_port; scalar_t__ connect_port; int /*<<< orphan*/  connect_path; int /*<<< orphan*/  connect_host; int /*<<< orphan*/  listen_path; int /*<<< orphan*/  listen_host; } ;

/* Variables and functions */
 scalar_t__ strcmp_maybe_null (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
forward_equals(const struct Forward *a, const struct Forward *b)
{
	if (strcmp_maybe_null(a->listen_host, b->listen_host) == 0)
		return 0;
	if (a->listen_port != b->listen_port)
		return 0;
	if (strcmp_maybe_null(a->listen_path, b->listen_path) == 0)
		return 0;
	if (strcmp_maybe_null(a->connect_host, b->connect_host) == 0)
		return 0;
	if (a->connect_port != b->connect_port)
		return 0;
	if (strcmp_maybe_null(a->connect_path, b->connect_path) == 0)
		return 0;
	/* allocated_port and handle are not checked */
	return 1;
}