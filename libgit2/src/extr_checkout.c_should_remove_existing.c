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
struct TYPE_3__ {int strategy; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ checkout_data ;

/* Variables and functions */
 int GIT_CHECKOUT_DONT_REMOVE_EXISTING ; 
 int /*<<< orphan*/  GIT_CONFIGMAP_IGNORECASE ; 
 scalar_t__ git_repository__configmap_lookup (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool should_remove_existing(checkout_data *data)
{
	int ignorecase;

	if (git_repository__configmap_lookup(&ignorecase, data->repo, GIT_CONFIGMAP_IGNORECASE) < 0) {
		ignorecase = 0;
	}

	return (ignorecase &&
		(data->strategy & GIT_CHECKOUT_DONT_REMOVE_EXISTING) == 0);
}