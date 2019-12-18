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
typedef  void* uint16_t ;
struct ieee80211_channel {int /*<<< orphan*/  ic_flags; int /*<<< orphan*/  ic_freq; } ;

/* Variables and functions */
 void* htole16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_channel(void *p, const struct ieee80211_channel *c)
{
	struct {
		uint16_t	freq;
		uint16_t	flags;
	} *rc = p;

	rc->freq = htole16(c->ic_freq);
	rc->flags = htole16(c->ic_flags);
}