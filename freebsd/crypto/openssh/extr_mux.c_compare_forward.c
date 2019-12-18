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
 int /*<<< orphan*/  compare_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_forward(struct Forward *a, struct Forward *b)
{
	if (!compare_host(a->listen_host, b->listen_host))
		return 0;
	if (!compare_host(a->listen_path, b->listen_path))
		return 0;
	if (a->listen_port != b->listen_port)
		return 0;
	if (!compare_host(a->connect_host, b->connect_host))
		return 0;
	if (!compare_host(a->connect_path, b->connect_path))
		return 0;
	if (a->connect_port != b->connect_port)
		return 0;

	return 1;
}