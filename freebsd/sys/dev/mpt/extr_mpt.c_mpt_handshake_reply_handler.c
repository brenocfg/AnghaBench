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
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  request_t ;
typedef  int /*<<< orphan*/  MSG_DEFAULT_REPLY ;

/* Variables and functions */
 int TRUE ; 

__attribute__((used)) static int
mpt_handshake_reply_handler(struct mpt_softc *mpt, request_t *req,
 uint32_t reply_desc, MSG_DEFAULT_REPLY *reply_frame)
{

	/* Nothing to be done. */
	return (TRUE);
}