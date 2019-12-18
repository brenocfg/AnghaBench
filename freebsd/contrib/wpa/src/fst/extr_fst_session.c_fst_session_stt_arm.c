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
struct fst_session {int /*<<< orphan*/  stt_armed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FST_DEFAULT_SESSION_TIMEOUT_TU ; 
 int /*<<< orphan*/  TRUE ; 
 int TU_TO_US (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fst_session*) ; 
 int /*<<< orphan*/  fst_session_timeout_handler ; 

__attribute__((used)) static void fst_session_stt_arm(struct fst_session *s)
{
	/* Action frames sometimes get delayed. Use relaxed timeout (2*) */
	eloop_register_timeout(0, 2 * TU_TO_US(FST_DEFAULT_SESSION_TIMEOUT_TU),
			       fst_session_timeout_handler, NULL, s);
	s->stt_armed = TRUE;
}