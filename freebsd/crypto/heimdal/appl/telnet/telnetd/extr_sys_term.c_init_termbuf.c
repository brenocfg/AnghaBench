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

/* Variables and functions */
 int /*<<< orphan*/  ourpty ; 
 scalar_t__ really_stream ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  termbuf ; 
 int /*<<< orphan*/  termbuf2 ; 
 int /*<<< orphan*/  ttyfd ; 

void
     init_termbuf(void)
{
# ifdef  STREAMSPTY
    if (really_stream)
	tcgetattr(ttyfd, &termbuf);
    else
# endif
	tcgetattr(ourpty, &termbuf);
    termbuf2 = termbuf;
}