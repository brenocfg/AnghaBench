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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ssh {int dummy; } ;
struct global_confirm {scalar_t__ ref_count; int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* cb ) (struct ssh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct global_confirm* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct global_confirm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  explicit_bzero (struct global_confirm*,int) ; 
 int /*<<< orphan*/  free (struct global_confirm*) ; 
 int /*<<< orphan*/  global_confirms ; 
 int /*<<< orphan*/  packet_set_alive_timeouts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ssh*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
client_global_request_reply(int type, u_int32_t seq, struct ssh *ssh)
{
	struct global_confirm *gc;

	if ((gc = TAILQ_FIRST(&global_confirms)) == NULL)
		return 0;
	if (gc->cb != NULL)
		gc->cb(ssh, type, seq, gc->ctx);
	if (--gc->ref_count <= 0) {
		TAILQ_REMOVE(&global_confirms, gc, entry);
		explicit_bzero(gc, sizeof(*gc));
		free(gc);
	}

	packet_set_alive_timeouts(0);
	return 0;
}