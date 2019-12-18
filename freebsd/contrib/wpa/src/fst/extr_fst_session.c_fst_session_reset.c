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
struct fst_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REASON_RESET ; 
 int /*<<< orphan*/  fst_session_reset_ex (struct fst_session*,int /*<<< orphan*/ ) ; 

void fst_session_reset(struct fst_session *s)
{
	fst_session_reset_ex(s, REASON_RESET);
}