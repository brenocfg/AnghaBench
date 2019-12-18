#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* free ) (TYPE_1__*) ;int /*<<< orphan*/  hash_ctx; } ;
typedef  TYPE_1__ git_odb_stream ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_hash_ctx_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void git_odb_stream_free(git_odb_stream *stream)
{
	if (stream == NULL)
		return;

	git_hash_ctx_cleanup(stream->hash_ctx);
	git__free(stream->hash_ctx);
	stream->free(stream);
}