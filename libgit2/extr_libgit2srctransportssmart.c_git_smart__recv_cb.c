#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  val; } ;
struct TYPE_7__ {int (* packetsize_cb ) (size_t,int /*<<< orphan*/ ) ;TYPE_5__ cancelled; int /*<<< orphan*/  packetsize_payload; TYPE_3__* current_stream; } ;
typedef  TYPE_1__ transport_smart ;
struct TYPE_8__ {size_t offset; scalar_t__ len; scalar_t__ data; scalar_t__ cb_data; } ;
typedef  TYPE_2__ gitno_buffer ;
struct TYPE_9__ {int (* read ) (TYPE_3__*,scalar_t__,scalar_t__,size_t*) ;} ;

/* Variables and functions */
 int GIT_EUSER ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  git_atomic_set (TYPE_5__*,int) ; 
 int stub1 (TYPE_3__*,scalar_t__,scalar_t__,size_t*) ; 
 int stub2 (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int git_smart__recv_cb(gitno_buffer *buf)
{
	transport_smart *t = (transport_smart *) buf->cb_data;
	size_t old_len, bytes_read;
	int error;

	assert(t->current_stream);

	old_len = buf->offset;

	if ((error = t->current_stream->read(t->current_stream, buf->data + buf->offset, buf->len - buf->offset, &bytes_read)) < 0)
		return error;

	buf->offset += bytes_read;

	if (t->packetsize_cb && !t->cancelled.val) {
		error = t->packetsize_cb(bytes_read, t->packetsize_payload);
		if (error) {
			git_atomic_set(&t->cancelled, 1);
			return GIT_EUSER;
		}
	}

	return (int)(buf->offset - old_len);
}