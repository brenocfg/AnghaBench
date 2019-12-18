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
struct mss_info {int dummy; } ;
struct mss_chinfo {int /*<<< orphan*/  buffer; struct mss_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int /*<<< orphan*/  mss_lock (struct mss_info*) ; 
 int /*<<< orphan*/  mss_trigger (struct mss_chinfo*,int) ; 
 int /*<<< orphan*/  mss_unlock (struct mss_info*) ; 
 int /*<<< orphan*/  sndbuf_dma (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
msschan_trigger(kobj_t obj, void *data, int go)
{
	struct mss_chinfo *ch = data;
	struct mss_info *mss = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return 0;

	sndbuf_dma(ch->buffer, go);
	mss_lock(mss);
	mss_trigger(ch, go);
	mss_unlock(mss);
	return 0;
}