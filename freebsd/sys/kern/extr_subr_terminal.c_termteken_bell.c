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
struct terminal {int /*<<< orphan*/  tm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TF_BELL ; 

__attribute__((used)) static void
termteken_bell(void *softc)
{
	struct terminal *tm = softc;

	tm->tm_flags |= TF_BELL;
}