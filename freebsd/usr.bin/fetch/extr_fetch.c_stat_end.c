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
struct xferstat {int /*<<< orphan*/  rcvd; int /*<<< orphan*/  last; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_bps (char*,int,struct xferstat*) ; 
 int /*<<< orphan*/  stat_bytes (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_display (struct xferstat*,int) ; 
 int /*<<< orphan*/  stat_eta (char*,int,struct xferstat*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ v_level ; 
 scalar_t__ v_progress ; 

__attribute__((used)) static void
stat_end(struct xferstat *xs)
{
	char bytes[16], bps[16], eta[16];

	gettimeofday(&xs->last, NULL);
	if (v_progress) {
		stat_display(xs, 2);
		putc('\n', stderr);
	} else if (v_level > 0) {
		stat_bytes(bytes, sizeof bytes, xs->rcvd);
		stat_bps(bps, sizeof bps, xs);
		stat_eta(eta, sizeof eta, xs);
		fprintf(stderr, "        %s %s %s\n", bytes, bps, eta);
	}
}