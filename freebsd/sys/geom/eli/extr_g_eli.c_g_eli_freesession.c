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
struct g_eli_worker {int /*<<< orphan*/  w_sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_freesession (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_eli_freesession(struct g_eli_worker *wr)
{

	crypto_freesession(wr->w_sid);
}