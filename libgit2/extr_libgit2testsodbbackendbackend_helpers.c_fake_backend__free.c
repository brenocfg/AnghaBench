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
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  fake_backend ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fake_backend__free(git_odb_backend *_backend)
{
	fake_backend *backend;

	backend = (fake_backend *)_backend;

	git__free(backend);
}