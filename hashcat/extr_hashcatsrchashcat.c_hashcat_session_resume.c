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
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
 int ResumeThreads (int /*<<< orphan*/ *) ; 

int hashcat_session_resume (hashcat_ctx_t *hashcat_ctx)
{
  return ResumeThreads (hashcat_ctx);
}