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
struct xencons_priv {unsigned int wp; unsigned int wc; } ;

/* Variables and functions */
 unsigned int WBUF_SIZE ; 
 int /*<<< orphan*/  xencons_lock (struct xencons_priv*) ; 
 int /*<<< orphan*/  xencons_unlock (struct xencons_priv*) ; 

__attribute__((used)) static bool
xencons_tx_full(struct xencons_priv *cons)
{
	unsigned int used;

	xencons_lock(cons);
	used = cons->wp - cons->wc;
	xencons_unlock(cons);

	return (used >= WBUF_SIZE);
}