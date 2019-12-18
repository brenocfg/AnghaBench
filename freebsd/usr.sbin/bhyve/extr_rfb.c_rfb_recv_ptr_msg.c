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
struct rfb_softc {int dummy; } ;
struct rfb_ptr_msg {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  button; } ;
typedef  int /*<<< orphan*/  ptr_msg ;

/* Variables and functions */
 int /*<<< orphan*/  console_ptr_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_read (int,void*,int) ; 

__attribute__((used)) static void
rfb_recv_ptr_msg(struct rfb_softc *rc, int cfd)
{
	struct rfb_ptr_msg ptr_msg;

	(void)stream_read(cfd, ((void *)&ptr_msg) + 1, sizeof(ptr_msg) - 1);

	console_ptr_event(ptr_msg.button, htons(ptr_msg.x), htons(ptr_msg.y));
}