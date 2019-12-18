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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;
struct TYPE_3__ {int /*<<< orphan*/  exists_calls; } ;
typedef  TYPE_1__ fake_backend ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 scalar_t__ GIT_OK ; 
 scalar_t__ search_object (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fake_backend__exists(git_odb_backend *backend, const git_oid *oid)
{
	fake_backend *fake;

	fake = (fake_backend *)backend;

	fake->exists_calls++;

	return search_object(NULL, fake, oid, GIT_OID_HEXSZ) == GIT_OK;
}