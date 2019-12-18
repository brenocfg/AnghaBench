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
struct uni_msg {int dummy; } ;
struct sscop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sscop_window (struct sscop*,int) ; 
 int /*<<< orphan*/  user_msgout (struct uni_msg*) ; 

__attribute__((used)) static void
uoutput(struct sscop *sscop, struct uni_msg *m)
{
	user_msgout(m);
	sscop_window(sscop, +1);
}