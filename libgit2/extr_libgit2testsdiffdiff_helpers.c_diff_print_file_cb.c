#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_diff_delta ;
struct TYPE_2__ {int /*<<< orphan*/  debug; } ;
typedef  TYPE_1__ diff_expects ;

/* Variables and functions */
 int diff_file_cb (int /*<<< orphan*/  const*,float,void*) ; 
 int /*<<< orphan*/  fprintf_delta (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,float) ; 
 int /*<<< orphan*/  stderr ; 

int diff_print_file_cb(
	const git_diff_delta *delta,
	float progress,
	void *payload)
{
	if (!payload) {
		fprintf_delta(stderr, delta, progress);
		return 0;
	}

	if (!((diff_expects *)payload)->debug)
		fprintf_delta(stderr, delta, progress);

	return diff_file_cb(delta, progress, payload);
}