#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cancel; int /*<<< orphan*/  read_flags; int /*<<< orphan*/  is_connected; int /*<<< orphan*/  ls; int /*<<< orphan*/  push; int /*<<< orphan*/  download_pack; int /*<<< orphan*/  negotiate_fetch; int /*<<< orphan*/  free; int /*<<< orphan*/  close; int /*<<< orphan*/  connect; int /*<<< orphan*/  set_custom_headers; int /*<<< orphan*/  set_callbacks; int /*<<< orphan*/  version; } ;
struct TYPE_7__ {TYPE_3__ parent; int /*<<< orphan*/  wrapped; int /*<<< orphan*/  heads; int /*<<< orphan*/  refs; int /*<<< orphan*/  rpc; int /*<<< orphan*/ * owner; } ;
typedef  TYPE_1__ transport_smart ;
typedef  int /*<<< orphan*/  git_transport ;
struct TYPE_8__ {scalar_t__ (* callback ) (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  param; int /*<<< orphan*/  rpc; } ;
typedef  TYPE_2__ git_smart_subtransport_definition ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_TRANSPORT_VERSION ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_smart__cancel ; 
 int /*<<< orphan*/  git_smart__close ; 
 int /*<<< orphan*/  git_smart__connect ; 
 int /*<<< orphan*/  git_smart__download_pack ; 
 int /*<<< orphan*/  git_smart__free ; 
 int /*<<< orphan*/  git_smart__is_connected ; 
 int /*<<< orphan*/  git_smart__ls ; 
 int /*<<< orphan*/  git_smart__negotiate_fetch ; 
 int /*<<< orphan*/  git_smart__push ; 
 int /*<<< orphan*/  git_smart__read_flags ; 
 int /*<<< orphan*/  git_smart__set_callbacks ; 
 int /*<<< orphan*/  git_smart__set_custom_headers ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ref_name_cmp ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 

int git_transport_smart(git_transport **out, git_remote *owner, void *param)
{
	transport_smart *t;
	git_smart_subtransport_definition *definition = (git_smart_subtransport_definition *)param;

	if (!param)
		return -1;

	t = git__calloc(1, sizeof(transport_smart));
	GIT_ERROR_CHECK_ALLOC(t);

	t->parent.version = GIT_TRANSPORT_VERSION;
	t->parent.set_callbacks = git_smart__set_callbacks;
	t->parent.set_custom_headers = git_smart__set_custom_headers;
	t->parent.connect = git_smart__connect;
	t->parent.close = git_smart__close;
	t->parent.free = git_smart__free;
	t->parent.negotiate_fetch = git_smart__negotiate_fetch;
	t->parent.download_pack = git_smart__download_pack;
	t->parent.push = git_smart__push;
	t->parent.ls = git_smart__ls;
	t->parent.is_connected = git_smart__is_connected;
	t->parent.read_flags = git_smart__read_flags;
	t->parent.cancel = git_smart__cancel;

	t->owner = owner;
	t->rpc = definition->rpc;

	if (git_vector_init(&t->refs, 16, ref_name_cmp) < 0) {
		git__free(t);
		return -1;
	}

	if (git_vector_init(&t->heads, 16, ref_name_cmp) < 0) {
		git__free(t);
		return -1;
	}

	if (definition->callback(&t->wrapped, &t->parent, definition->param) < 0) {
		git__free(t);
		return -1;
	}

	*out = (git_transport *) t;
	return 0;
}