#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cancel; int /*<<< orphan*/  read_flags; int /*<<< orphan*/  is_connected; int /*<<< orphan*/  ls; int /*<<< orphan*/  free; int /*<<< orphan*/  close; int /*<<< orphan*/  push; int /*<<< orphan*/  download_pack; int /*<<< orphan*/  negotiate_fetch; int /*<<< orphan*/  connect; int /*<<< orphan*/  set_callbacks; int /*<<< orphan*/  version; } ;
struct TYPE_7__ {int /*<<< orphan*/ * owner; int /*<<< orphan*/  refs; TYPE_1__ parent; } ;
typedef  TYPE_2__ transport_local ;
typedef  int /*<<< orphan*/  git_transport ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_TRANSPORT_VERSION ; 
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int git_vector_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_cancel ; 
 int /*<<< orphan*/  local_close ; 
 int /*<<< orphan*/  local_connect ; 
 int /*<<< orphan*/  local_download_pack ; 
 int /*<<< orphan*/  local_free ; 
 int /*<<< orphan*/  local_is_connected ; 
 int /*<<< orphan*/  local_ls ; 
 int /*<<< orphan*/  local_negotiate_fetch ; 
 int /*<<< orphan*/  local_push ; 
 int /*<<< orphan*/  local_read_flags ; 
 int /*<<< orphan*/  local_set_callbacks ; 

int git_transport_local(git_transport **out, git_remote *owner, void *param)
{
	int error;
	transport_local *t;

	GIT_UNUSED(param);

	t = git__calloc(1, sizeof(transport_local));
	GIT_ERROR_CHECK_ALLOC(t);

	t->parent.version = GIT_TRANSPORT_VERSION;
	t->parent.set_callbacks = local_set_callbacks;
	t->parent.connect = local_connect;
	t->parent.negotiate_fetch = local_negotiate_fetch;
	t->parent.download_pack = local_download_pack;
	t->parent.push = local_push;
	t->parent.close = local_close;
	t->parent.free = local_free;
	t->parent.ls = local_ls;
	t->parent.is_connected = local_is_connected;
	t->parent.read_flags = local_read_flags;
	t->parent.cancel = local_cancel;

	if ((error = git_vector_init(&t->refs, 0, NULL)) < 0) {
		git__free(t);
		return error;
	}

	t->owner = owner;

	*out = (git_transport *) t;

	return 0;
}