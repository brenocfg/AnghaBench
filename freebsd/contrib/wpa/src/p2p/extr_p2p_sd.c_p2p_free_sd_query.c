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
struct p2p_sd_query {int /*<<< orphan*/  tlvs; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct p2p_sd_query*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void p2p_free_sd_query(struct p2p_sd_query *q)
{
	if (q == NULL)
		return;
	wpabuf_free(q->tlvs);
	os_free(q);
}