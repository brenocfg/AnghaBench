#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {TYPE_3__* backend; } ;
typedef  TYPE_1__ git_odb_stream ;
struct TYPE_6__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ fake_wstream ;
struct TYPE_7__ {int (* write ) (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fake_wstream__fwrite(git_odb_stream *_stream, const git_oid *oid)
{
	fake_wstream *stream = (fake_wstream *)_stream;
	return _stream->backend->write(_stream->backend, oid, stream->buffer, stream->size, stream->type);
}