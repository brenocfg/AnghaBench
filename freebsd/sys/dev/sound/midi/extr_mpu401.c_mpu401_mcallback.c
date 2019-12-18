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
struct snd_midi {int dummy; } ;
struct mpu401 {int flags; int /*<<< orphan*/  timer; scalar_t__ si; } ;

/* Variables and functions */
 int M_RX ; 
 int M_RXEN ; 
 int M_TX ; 
 int M_TXEN ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct mpu401*) ; 
 int /*<<< orphan*/  mpu401_timeout ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void
mpu401_mcallback(struct snd_midi *sm, void *arg, int flags)
{
	struct mpu401 *m = arg;
#if 0
	printf("mpu401_callback %s %s %s %s\n",
	    flags & M_RX ? "M_RX" : "",
	    flags & M_TX ? "M_TX" : "",
	    flags & M_RXEN ? "M_RXEN" : "",
	    flags & M_TXEN ? "M_TXEN" : "");
#endif
	if (flags & M_TXEN && m->si) {
		callout_reset(&m->timer, 1, mpu401_timeout, m);
	}
	m->flags = flags;
}