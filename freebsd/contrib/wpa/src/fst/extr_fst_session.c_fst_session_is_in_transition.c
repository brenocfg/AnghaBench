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
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */

__attribute__((used)) static Boolean fst_session_is_in_transition(struct fst_session *s)
{
	/* See spec, 10.32.2.2  Transitioning between states */
	return s->stt_armed;
}