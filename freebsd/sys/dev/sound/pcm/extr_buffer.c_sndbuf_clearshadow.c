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
struct snd_dbuf {scalar_t__ sl; int /*<<< orphan*/  fmt; int /*<<< orphan*/ * shadbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sndbuf_zerodata (int /*<<< orphan*/ ) ; 

void
sndbuf_clearshadow(struct snd_dbuf *b)
{
	KASSERT(b != NULL, ("b is a null pointer"));
	KASSERT(b->sl >= 0, ("illegal shadow length"));

	if ((b->shadbuf != NULL) && (b->sl > 0))
		memset(b->shadbuf, sndbuf_zerodata(b->fmt), b->sl);
}