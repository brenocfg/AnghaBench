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
typedef  int /*<<< orphan*/  u16 ;
struct request {scalar_t__ request; int /*<<< orphan*/  trans_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
request_trans_id_set(struct request *const req, const u16 trans_id) {
	req->trans_id = trans_id;
	*((u16 *) req->request) = htons(trans_id);
}