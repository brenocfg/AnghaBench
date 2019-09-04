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
typedef  int /*<<< orphan*/  git_transport ;

/* Variables and functions */
 int /*<<< orphan*/  _transport ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_transport ; 
 int /*<<< orphan*/  git_transport_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_transport_register (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transport_unregister (char*) ; 

void test_transport_register__custom_transport(void)
{
	git_transport *transport;

	cl_git_pass(git_transport_register("something", dummy_transport, NULL));

	cl_git_pass(git_transport_new(&transport, NULL, "something://somepath"));

	cl_assert(transport == &_transport);

	cl_git_pass(git_transport_unregister("something"));
}